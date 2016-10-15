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
, pPrefabCreate(shNULL)
, pPrefabFind(shNULL)
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
	pPrefabCreate = shNULL;
	pPrefabFind = shNULL;
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

	pPrefabCreate = ShPrefab::Create(levelIdentifier, CShIdentifier("bloc_pierre_001"), CShIdentifier("bloc_pierre"), CShIdentifier("layer_default"), CShVector3(0.0f, 0.0f, 1.0f), CShEulerAngles(), CShVector3(1.0f, 1.0f, 1.0f));
	SH_ASSERT(shNULL != pPrefabCreate);

	_bBlockTest = new Block(pPrefabCreate);

	/*pPrefabFind = ShPrefab::Find(levelIdentifier, CShIdentifier("prefab_bloc_pierre_001"));
	SH_ASSERT(shNULL != pPrefabFind);*/

	FieldManager fm(CShVector2(10, 10));

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
			_bBlockTest->Update();
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