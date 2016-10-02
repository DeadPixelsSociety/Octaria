//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateManager.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

CGameStateManager g_gameStateManager;

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGameStateManager::CGameStateManager(void)
: m_sGameState(2)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ CGameStateManager::~CGameStateManager(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateManager::Initialize(void)
{
	m_apGameState[e_game_state_main_menu] = new CGameStateGameMainMenu();
	SH_ASSERT(shNULL != m_apGameState[e_game_state_main_menu]);
	m_apGameState[e_game_state_main_menu]->Initialize();
	
	Push(e_game_state_main_menu);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateManager::Release(void)
{
	for (int eGameState = 0 ; eGameState < e_game_state_max ; ++eGameState)
	{
		SH_SAFE_RELEASE_DELETE(m_apGameState[eGameState]);
	}

	m_sGameState.Empty();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateManager::Update(float deltaTimeInMs)
{
	if (shNULL != GetCurrentGameState())
	{
		GetCurrentGameState()->Update(deltaTimeInMs);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateManager::Push(EGameState eGameState)
{
	CGameState * pCurrentGameState = GetCurrentGameState();
	if (shNULL != pCurrentGameState)
	{
		pCurrentGameState->DeActivate();
	}

	m_apGameState[eGameState]->Activate();
	m_sGameState.Push(m_apGameState[eGameState]);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGameStateManager::Pop(void)
{
	CGameState * pCurrentGameState = GetCurrentGameState();
	if (shNULL != pCurrentGameState)
	{
		pCurrentGameState->DeActivate();
	}

	m_sGameState.Pop(pCurrentGameState);
	
	if (shNULL != GetCurrentGameState())
	{
		GetCurrentGameState()->Activate();
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
CGameState * CGameStateManager::GetCurrentGameState(void)
{
	if (m_sGameState.IsEmpty())
	{
		return(shNULL);
	}

	return(m_sGameState.GetTop());
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateManager::OnTouchDown(int iTouch, float positionX, float positionY)
{
	GetCurrentGameState()->OnTouchDown(iTouch, positionX, positionY);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateManager::OnTouchUp(int iTouch, float positionX, float positionY)
{
	GetCurrentGameState()->OnTouchUp(iTouch, positionX, positionY);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void CGameStateManager::OnTouchMove(int iTouch, float positionX, float positionY)
{
	GetCurrentGameState()->OnTouchMove(iTouch, positionX, positionY);
}

