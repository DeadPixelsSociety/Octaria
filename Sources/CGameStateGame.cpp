//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateGame.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGameStateGame::CGameStateGame(void)
: CGameState()
, m_eState(e_state_enter)
, m_aPoulpeList()
, m_aBlockList()
, m_pCurrentPoulpe(shNULL)
, m_mouseClic(0)
, m_pCurrentPlayer(shNULL)
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
	// Field generation
	int nbBlocX = 90;
	int nbBlocY = 48;
	int nBlockCount = nbBlocX * nbBlocY;
	float blocWidth  = 64.0f;	// hardcoded value, getting from sprite
	float blocHeight = 64.0f;	// ^	

	FieldManager fieldManager(CShVector2(nbBlocX, nbBlocY));

	CShArray<EBlocValue> aFieldBlockType;
	fieldManager.GetFieldBlockType(aFieldBlockType);
	SH_ASSERT(nBlockCount == aFieldBlockType.GetCount());

	CShArray<CShVector2> aFieldCoord;
	fieldManager.GetFieldCoord(aFieldCoord);
	SH_ASSERT(nBlockCount == aFieldCoord.GetCount());

	// add grass layer
	for (int x = 0; x < nbBlocX; ++x)
	{
		for (int y = nbBlocY - 1; 0 <= y; --y)
		{
			if (e_bloc_vide != aFieldBlockType[(x*nbBlocY) + y])
			{
				int lastCase = (x*nbBlocY) + y + 1;
				if (nbBlocY - 1 == y)
				{
					--lastCase;
				}

				aFieldBlockType[lastCase] = e_bloc_herbe;

				break;
			}
		}
	}

	//
	// Get n°0 bloc coord
	float coordX = 0.0f;
	float coordY = 0.0f;

	coordX -= ((nbBlocX / 2) * blocWidth);
	if (0 != (nbBlocX % 2))
	{
		coordX -= blocWidth / 2;
	}

	coordY -= ((nbBlocY / 2) * blocHeight);
	if (0 != (nbBlocY % 2))
	{
		coordY -= blocHeight / 2;
	}

	//
	// Generate and place all blocs
	for (int i = 0; i < nBlockCount; ++i)
	{
		if (e_bloc_vide != aFieldBlockType[i])
		{
			float currentX, currentY;
			currentX = coordX + (blocWidth * aFieldCoord[i].m_x);
			currentY = coordY + (blocHeight * aFieldCoord[i].m_y);
			ShPrefab * pPrefab = ShPrefab::Create(levelIdentifier, CShIdentifier("ntm"), CShIdentifier(g_aPrefabName[aFieldBlockType[i]]), CShIdentifier("layer_default"), CShVector3(currentX, currentY, 1.0f), CShEulerAngles(), CShVector3(1.0f, 1.0f, 1.0f));
			SH_ASSERT(shNULL != pPrefab);

			Block * pBlock = new Block();
			pBlock->Initialize(pPrefab, aFieldBlockType[i]);

			m_aBlockList.Add(pBlock);
		}
		else // void bloc
		{
			m_aBlockList.Add(shNULL);
		}
	}

	//
	// Character
	CGamePoulpe * pPoulpe = new (CGamePoulpe);
	pPoulpe->Initialize(levelIdentifier);
	m_aPoulpeList.Add(pPoulpe);

	m_pCurrentPoulpe = m_aPoulpeList[0];

	//
	// Player
	CGamePlayer * pPlayer = new CGamePlayer();
	m_pCurrentPlayer = pPlayer;

	m_eState = e_state_enter;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::DeActivate(void)
{
	m_pCurrentPoulpe = shNULL;

	int nPoulpeCount = m_aPoulpeList.GetCount();
	for (int iPoulpe = 0; iPoulpe < nPoulpeCount; ++iPoulpe)
	{
		m_aPoulpeList[iPoulpe]->Release();
		SH_SAFE_DELETE(m_aPoulpeList[iPoulpe]);
	}
	m_aPoulpeList.Empty();

	int nBlockCount = m_aBlockList.GetCount();
	for (int iBlock = 0; iBlock < nPoulpeCount; ++iBlock)
	{
		m_aBlockList[iBlock]->Release();
		SH_SAFE_DELETE(m_aPoulpeList[iBlock]);
	}
	m_aBlockList.Empty();

	m_pCurrentPlayer->Release();
	m_pCurrentPlayer = shNULL;
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
			g_pInputPlayer->Update();

			bool isLeft		= g_pInputPlayer->IsLeftPressed();
			bool isRight	= g_pInputPlayer->IsRightPressed();
			bool isDown		= g_pInputPlayer->IsDownPressed();
			bool isUp		= g_pInputPlayer->IsUpPressed();

			m_pCurrentPoulpe->Update(isLeft, isRight, isDown, isUp);
			
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
						m_aBlockList[iBlock] = shNULL;
					}
				}
			}
		}
	}
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