//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateMainMenu.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGameStateMainMenu::CGameStateMainMenu(void)
: CGameState()
, m_eState(e_state_enter)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ CGameStateMainMenu::~CGameStateMainMenu(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::Initialize(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::Release(void)
{
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::Activate(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("octa_level_main_menu");
	bool resLoad = ShLevel::Load(levelIdentifier);
	SH_ASSERT(resLoad);

	m_eState = e_state_enter;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::DeActivate(void)
{
	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::Update(float deltaTimeInMs)
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
		}break;
		
		case e_state_end:
		{
			g_gameStateManager.Pop();
			g_gameStateManager.Push(CGameStateManager::e_game_state_game);
		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::OnTouchDown(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateMainMenu::OnTouchMove(int iTouch, float positionX, float positionY)
{

}