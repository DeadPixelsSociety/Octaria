//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : StdAfx.h
// Author      : PRADAL & co
// Description : -
// Platform    : All
//--------------------------------------------------------------------------------------------------

#ifndef __SHPROJECT_OCTARIA_STDAFX_H
#define __SHPROJECT_OCTARIA_STDAFX_H

// Internal Height/Width
#define DISPLAY_HEIGHT 1536
#define DISPLAY_WIDTH 2272

#define DISPLAY_HALF_HEIGHT 768
#define DISPLAY_HALF_WIDTH 1136

//
// Game data

enum EBlocValue
{
	e_bloc_vide,		//<	default
	e_bloc_herbe,		//<
	e_bloc_terre,		//<
	e_bloc_pierre,		//<	
	e_bloc_charbon,		//<

	e_bloc_max
};

static const char * g_aPrefabName[e_bloc_max] =
{
	"bloc_vide",		//< not used, void bloc
	"bloc_herbe",		//< 
	"bloc_terre",		//<
	"bloc_pierre",		//< 
	"bloc_charbon",		//<
};

//
// Shine SDK includes
#include "ShSDK/ShSDK.h"

#include "Block.h"
#include "FieldManager.h"
#include "ProceduralGeneration.h"

#include "CMultiResolutionApplication.h"

#include "Inputs.h"

#include "CGamePoulpe.h"

#include "CGameState.h"
#include "CGameStateManager.h"

#include "CGameStateGame.h"
#include "CGameStateMainMenu.h"


//
// Project callbacks
void OnActivate(void);
void OnDeactivate(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs);
void OnSaveResult(int status);
void OnLoadResult(int status);

void OnLogin(ShUser * pUser);
void OnLogout(ShUser * pUser);
void OnUserChanged(ShUser * pUser);

void OnTouchDown(int iTouch, float positionX, float positionY);
void OnTouchUp(int iTouch, float positionX, float positionY);
void OnTouchMove(int iTouch, float positionX, float positionY);


extern CShArray<ShUser*> g_aUsers;
extern ShUser * g_pCurrentUser;
extern Inputs * g_pInputPlayer;

void SetCurrentUser(ShUser * pUser);


#endif // __SHPROJECT_OCTARIA_STDAFX_H