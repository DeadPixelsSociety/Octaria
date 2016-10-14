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

	CGamePoulpe * pPoulpe = new (CGamePoulpe);
	pPoulpe->Initialize(levelIdentifier);
	m_aPoulpeList.Add(pPoulpe);

	m_eState = e_state_enter;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::DeActivate(void)
{
	int nPoulpeCount = m_aPoulpeList.GetCount();
	for (int iPoulpe = 0; iPoulpe < nPoulpeCount; ++iPoulpe)
	{
		m_aPoulpeList[iPoulpe]->Release();
		SH_SAFE_DELETE(m_aPoulpeList[iPoulpe]);
	}
	m_aPoulpeList.Empty();
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

			int nPoulpeCount = m_aPoulpeList.GetCount();
			for (int iPoulpe = 0; iPoulpe < nPoulpeCount; ++iPoulpe)
			{
				m_aPoulpeList[iPoulpe]->Update(isLeft, isRight);
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
/*virtual*/ void CGameStateGame::OnTouchDown(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGame::OnTouchMove(int iTouch, float positionX, float positionY)
{

}