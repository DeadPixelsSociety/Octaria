//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateGame.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

#define NB_BLOC_X 90
#define NB_BLOC_Y 48

#define BLOC_EDGE_LENGTH 64

#define NB_POULPE_PER_TEAM 3

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGameStateGame::CGameStateGame(void)
: CGameState()
, m_eState(e_state_enter)
, m_aBlockList()
, m_pCurrentPoulpe(shNULL)
, m_mouseClic(0)
, m_pCurrentPlayer(shNULL)
, m_pWorld(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ CGameStateGame::~CGameStateGame(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::Initialize(void)
{
	srand(time(shNULL));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::Release(void)
{
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::Activate(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("octa_level_game");
	bool resLoad = ShLevel::Load(levelIdentifier);
	SH_ASSERT(resLoad);

	//
	// Box2D
	//b2Vec2 gravity(0.0f, 0.0f);
	b2Vec2 gravity(0.0f, -1000.0f);
	m_pWorld = new b2World(gravity);

	//
	// Procedural map
	GenerateGameMap(levelIdentifier);

	//
	// Player
	m_pPlayer1 = new CGamePlayer();
	m_pCurrentPlayer = m_pPlayer1;

	//
	// Character
	for (int i = 0; i < NB_POULPE_PER_TEAM; ++i)
	{
		CShVector2 randPos;
		GetFreePos(randPos);
		CGamePoulpe * pPoulpe = new CGamePoulpe();
		pPoulpe->Initialize(levelIdentifier, m_pWorld, randPos);
		m_pPlayer1->AddPoulpeToList(pPoulpe);
	}

	// TODO poulpe team 2 with other color

	m_pCurrentPoulpe = m_pCurrentPlayer->GetPoulpeToPlay();

	//
	// Misc

	ShCamera::SetPosition(g_pCamera, CShVector3(m_pCurrentPoulpe->GetPosition(), 2000.0f));
	ShCamera::SetTarget(g_pCamera, CShVector3(m_pCurrentPoulpe->GetPosition(), 0.0f));

	m_eState = e_state_enter;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::DeActivate(void)
{
	m_pCurrentPoulpe = shNULL;
	m_pCurrentPlayer = shNULL;

	int nBlockCount = m_aBlockList.GetCount();
	for (int iBlock = 0; iBlock < nBlockCount; ++iBlock)
	{
		if (shNULL != m_aBlockList[iBlock])
		{
			m_aBlockList[iBlock]->Release(m_pWorld);
			SH_SAFE_DELETE(m_aBlockList[iBlock]);
		}
	}
	m_aBlockList.Empty();

	m_pPlayer1->Release();
	m_pPlayer1 = shNULL;
	m_pPlayer2->Release();
	m_pPlayer2 = shNULL;

	SH_SAFE_DELETE(m_pWorld);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::Update(float deltaTimeInMs)
{
	switch(m_eState)
	{
		case e_state_enter:
		{
			// intitialize what you need
			m_eState = e_state_playing;
		}
		break;

		case e_state_playing:
		{
			//
			// Update Box2D world
			{
				// TODO : clamp steps
				float32 timeStep = 1 / 20.0f;    //the length of time passed to simulate (seconds)
				int32 velocityIterations = 8;   //how strongly to correct velocity
				int32 positionIterations = 3;   //how strongly to correct position

				m_pWorld->Step(timeStep, velocityIterations, positionIterations);
			}

			g_pInputPlayer->Update();

			bool isLeft		= g_pInputPlayer->IsLeftPressed();
			bool isRight	= g_pInputPlayer->IsRightPressed();
			bool isDown		= g_pInputPlayer->IsDownPressed();
			bool isUp		= g_pInputPlayer->IsUpPressed();
			bool isJump		= g_pInputPlayer->IsJumpPressed();

			m_pCurrentPoulpe->Update(isLeft, isRight, isDown, isUp, isJump);
			
			if (m_mouseClic)
			{
				PlayerMining();
			}

		}break;
		
		case e_state_end:
		{
			g_gameStateManager.Pop();
			g_gameStateManager.Push(CGameStateManager::e_game_state_main_menu);
		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateGame::GenerateGameMap(const CShIdentifier & levelIdentifier)
{
	int nBlockCount = NB_BLOC_X * NB_BLOC_Y;

	//
	// Generate 1D field
	FieldManager fieldManager1D(CShVector2(NB_BLOC_X, NB_BLOC_Y));
	fieldManager1D.Initialize(true);
	fieldManager1D.GenerateMap();

	CShArray<EBlocType> aFieldBlockType;
	fieldManager1D.GetFieldBlockType(aFieldBlockType);
	SH_ASSERT(nBlockCount == aFieldBlockType.GetCount());

	CShArray<CShVector2> aFieldCoord;
	fieldManager1D.GetFieldCoord(aFieldCoord);
	SH_ASSERT(nBlockCount == aFieldCoord.GetCount());

	// add grass layer
	for (int x = 0; x < NB_BLOC_X; ++x)
	{
		for (int y = NB_BLOC_Y - 1; 0 <= y; --y)
		{
			if (e_bloc_vide != aFieldBlockType[(x*NB_BLOC_Y) + y])
			{
				int lastCase = (x*NB_BLOC_Y) + y + 1;
				if (NB_BLOC_Y - 1 == y)
				{
					--lastCase;
				}

				aFieldBlockType[lastCase] = e_bloc_herbe;

				break;
			}
		}
	}

	//
	// Generate 2D field
	CShArray<EBlocType> aMergedFieldBlockType;
	FieldManager fieldManager2D(CShVector2(NB_BLOC_X, NB_BLOC_Y));
	fieldManager2D.Initialize(false);
	fieldManager2D.GenerateMap();

	fieldManager2D.MergeMap(aFieldBlockType, aMergedFieldBlockType);

	SH_ASSERT(nBlockCount == aMergedFieldBlockType.GetCount());

	//
	// Get n°0 bloc coord
	float coordX = 0.0f;
	float coordY = 0.0f;

	coordX -= ((NB_BLOC_X / 2) * BLOC_EDGE_LENGTH);
	if (0 != (NB_BLOC_X % 2))
	{
		coordX -= BLOC_EDGE_LENGTH / 2;
	}

	coordY -= ((NB_BLOC_Y / 2) * BLOC_EDGE_LENGTH);
	if (0 != (NB_BLOC_Y % 2))
	{
		coordY -= BLOC_EDGE_LENGTH / 2;
	}

	//
	// Generate and place all blocs
	for (int i = 0; i < nBlockCount; ++i)
	{
		if (e_bloc_vide != aMergedFieldBlockType[i])
		{
			float currentX, currentY;
			currentX = coordX + (BLOC_EDGE_LENGTH * aFieldCoord[i].m_x);
			currentY = coordY + (BLOC_EDGE_LENGTH * aFieldCoord[i].m_y);
			ShPrefab * pPrefab = ShPrefab::Create(levelIdentifier, CShIdentifier("ntm"), CShIdentifier(g_aPrefabName[aMergedFieldBlockType[i]]), CShIdentifier("layer_default"), CShVector3(currentX, currentY, 1.0f), CShEulerAngles(), CShVector3(1.0f, 1.0f, 1.0f));
			SH_ASSERT(shNULL != pPrefab);

			Block * pBlock = new Block();
			pBlock->Initialize(pPrefab, aMergedFieldBlockType[i], m_pWorld);

			m_aBlockList.Add(pBlock);
		}
		else // void bloc
		{
			m_aBlockList.Add(shNULL);
		}
	}

	fieldManager1D.Release();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateGame::PlayerMining(void)
{
	CShVector2 posPlayer = m_pCurrentPoulpe->GetPosition();
	EPoulpeLook dirLook = m_pCurrentPoulpe->GetLook();

	CShVector2 posRay(posPlayer);

	switch (dirLook)
	{
		case e_look_right:
		{
			posRay.m_x += 32.0f;
		}break;

		case e_look_left:
		{
			posRay.m_x -= 32.0f;
		}break;

		case e_look_up:
		{
			posRay.m_y += 32.0f;
		}break;

		case e_look_down:
		{
			posRay.m_y -= 32.0f;
		}break;
	}

	int nBlockCount = m_aBlockList.GetCount();
	for (int iBlock = 0; iBlock < nBlockCount; ++iBlock)
	{
		Block * pBlock = m_aBlockList[iBlock];
		// Avoid void bloc
		if (shNULL != pBlock)
		{
			CShVector2 posBlock = pBlock->GetPosition();
			if (32.0f >= computeVecteurNorme(posBlock.m_x, posBlock.m_y, posRay.m_x, posRay.m_y))
			{
				if (e_bloc_vide != pBlock->GetType())
				{
					if (pBlock->HitByPlayer())
					{
						m_pCurrentPlayer->AddObjectToIventory(pBlock->GetType());
						ShEntity2::SetShow(m_aBlockList[iBlock]->GetEntity(), false);
						m_aBlockList[iBlock]->Release(m_pWorld);
						m_aBlockList[iBlock] = shNULL; // transform to void
					}
					break;
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateGame::GetFreePos(CShVector2 & randPos)
{
	CShArray<int> freePosList;
	int randRaw;

	while (freePosList.IsEmpty())
	{
		randRaw = rand() % NB_BLOC_X;
		for (int y = 0; y < NB_BLOC_Y - 1; ++y)
		{
			int currentBloc = (randRaw*NB_BLOC_Y) + y;
			if (shNULL != m_aBlockList[currentBloc])
			{
				if (e_bloc_herbe == m_aBlockList[currentBloc]->GetType())
				{
					freePosList.Add(y);
				}
			}
		}
	}

	int randId = 0;
	int nbFreePos = freePosList.GetCount();
	if (1 < nbFreePos)
	{
		randId = rand() % nbFreePos;
	}

	SH_ASSERT(shNULL != m_aBlockList[(randRaw*NB_BLOC_Y) + freePosList[randId]]);

	const CShVector2 & herbeBlocPos = m_aBlockList[(randRaw*NB_BLOC_Y) + freePosList[randId]]->GetPosition();

	randPos.m_x = herbeBlocPos.m_x;
	randPos.m_y = herbeBlocPos.m_y + BLOC_EDGE_LENGTH;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::OnTouchDown(int iTouch, float positionX, float positionY)
{
	m_mouseClic = 1;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::OnTouchUp(int iTouch, float positionX, float positionY)
{
	m_mouseClic = 0;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::OnTouchMove(int iTouch, float positionX, float positionY)
{
	m_pCurrentPoulpe->SetLook(positionX, positionY);
}