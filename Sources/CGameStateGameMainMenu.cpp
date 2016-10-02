//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateGameMainMenu.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGameStateGameMainMenu::CGameStateGameMainMenu(void)
: CGameState()
, m_eState(e_state_enter)
, m_pCreatedPoulpe(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ CGameStateGameMainMenu::~CGameStateGameMainMenu(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::Initialize(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::Release(void)
{
	m_pCreatedPoulpe = shNULL;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::Activate(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("octa_level_main_menu");
	bool resLoad = ShLevel::Load(levelIdentifier);
	SH_ASSERT(resLoad);

	m_pCreatedPoulpe = ShEntity2::Create(levelIdentifier, GID(NULL), GID(layer_default), CShIdentifier("octaria"), CShIdentifier("icone_poulpe"), CShVector3(-100.0f, -100.0f, 1.0f), CShEulerAngles(), CShVector3(5.0f, 5.0f, 1.0f));
	SH_ASSERT(shNULL != m_pCreatedPoulpe);

	m_eState = e_state_enter;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::DeActivate(void)
{
	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::Update(float deltaTimeInMs)
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
			bool isUp		= g_pInputPlayer->IsUpPressed();
			bool isDown		= g_pInputPlayer->IsDownPressed();

			CShVector2 currentPos = ShEntity2::GetWorldPosition2(m_pCreatedPoulpe);

			if (isLeft)
			{
				currentPos.m_x -= 5.0f;
			}
			else if (isRight)
			{
				currentPos.m_x += 5.0f;
			}

			if (isUp)
			{
				currentPos.m_y += 5.0f;
			}
			else if (isDown)
			{
				currentPos.m_y -= 5.0f;
			}

			ShEntity2::SetWorldPosition2(m_pCreatedPoulpe, currentPos.m_x, currentPos.m_y);

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
/*virtual*/ void CGameStateGameMainMenu::OnTouchDown(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateGameMainMenu::OnTouchMove(int iTouch, float positionX, float positionY)
{

}