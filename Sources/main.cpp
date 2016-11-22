//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : main.cpp
// Author      : PRADAL & co
// Description : -
// Platform    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

#include "ShEntryPoint/ShEntryPoint.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
CMultiResolutionApplication	g_multiResolutionApplication;
float						g_rescaleFactor = 1.0f;
ShCamera * g_pCamera = shNULL;

//
// Users
CShArray<ShUser *> g_aUsers;
ShUser * g_pCurrentUser = shNULL;
Inputs * g_pInputPlayer = shNULL;

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ShEntryPoint::OnPreInitialize(void)
{
	ShApplication::SetOnActivate(OnActivate);
	ShApplication::SetOnDeactivate(OnDeactivate);

	ShApplication::SetOnSaveResult(OnSaveResult);
	ShApplication::SetOnLoadResult(OnLoadResult);

	//---------------------------------------------------------------------------

	ShUser::RegisterLoginCallback(OnLogin);
	ShUser::RegisterLogoutCallback(OnLogout);
	ShUser::RegisterUserChangedCallback(OnUserChanged);

	ShInput::AddOnTouchDown(OnTouchDown);
	ShInput::AddOnTouchUp(OnTouchUp);
	ShInput::AddOnTouchMove(OnTouchMove);

	//---------------------------------------------------------------------------

	g_multiResolutionApplication.OnPreInitialize();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ShEntryPoint::OnPostInitialize(void)
{
	//
	// Create camera
	g_pCamera = ShCamera::Create(GID(global), GID(camera_free), false);
	SH_ASSERT(shNULL != g_pCamera);

	ShCamera::SetPosition(g_pCamera, CShVector3(0.0f, 0.0f, 4000.0f));
	ShCamera::SetTarget(g_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetUp(g_pCamera, CShVector3(0.0f, 1.0f, 0.0f));
	ShCamera::SetNearPlaneDistance(g_pCamera, 1.0f);
	ShCamera::SetFarPlaneDistance(g_pCamera, 10000.0f);

	int displayWidth = ShDisplay::GetWidth(); // 1280
	int displayHeight = ShDisplay::GetHeight(); // 720

	float displayAspectRatio = 1.0f;

	if (displayWidth >= displayHeight)
	{
		// Horizontal display
		displayAspectRatio = (float)displayWidth / (float)displayHeight;
	}
	else
	{
		// Vertical display
		displayAspectRatio = (float)displayHeight / (float)displayWidth;
	}

	if (displayAspectRatio < (DISPLAY_WIDTH / DISPLAY_HEIGHT))
	{
		g_rescaleFactor = DISPLAY_HEIGHT / displayHeight;
	}
	else
	{
		g_rescaleFactor = DISPLAY_WIDTH / displayWidth;
	}

	ShCamera::SetViewport(g_pCamera, g_rescaleFactor * displayWidth, g_rescaleFactor * displayHeight);
	ShCamera::SetCurrent2D(g_pCamera);
	g_multiResolutionApplication.SetCamera(g_pCamera);

	//
	// Initialize multi resolution application
	g_multiResolutionApplication.OnPostInitialize();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ShEntryPoint::OnPreUpdate(float deltaTimeInMs)
{
	g_multiResolutionApplication.OnPreUpdate(deltaTimeInMs);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ShEntryPoint::OnPostUpdate(float deltaTimeInMs)
{
	g_multiResolutionApplication.OnPostUpdate(deltaTimeInMs);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ShEntryPoint::OnPreRelease(void)
{
	g_multiResolutionApplication.OnPreRelease();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ShEntryPoint::OnPostRelease(void)
{
	g_multiResolutionApplication.OnPostRelease();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnActivate(void)
{
	g_multiResolutionApplication.OnActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnDeactivate(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs)
{
	g_multiResolutionApplication.OnDeactivate();

	bAllowBackgroundUpdates = false;
	bAllowBackgroundInputs = false;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnSaveResult(int status)
{
	//TODO
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnLoadResult(int status)
{
	//TODO
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnTouchDown(int iTouch, float positionX, float positionY)
{
	g_multiResolutionApplication.OnTouchDown(iTouch, positionX * g_rescaleFactor, positionY * g_rescaleFactor);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnTouchUp(int iTouch, float positionX, float positionY)
{
	g_multiResolutionApplication.OnTouchUp(iTouch, positionX * g_rescaleFactor, positionY * g_rescaleFactor);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnTouchMove(int iTouch, float positionX, float positionY)
{
	g_multiResolutionApplication.OnTouchMove(iTouch, positionX * g_rescaleFactor, positionY * g_rescaleFactor);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnLogin(ShUser * pUser)
{
	SetCurrentUser(pUser);
	g_pInputPlayer = new Inputs();
	g_pInputPlayer->Initialize(g_pCurrentUser);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnLogout(ShUser * pUser)
{
	if (pUser == g_pCurrentUser)
	{
		SetCurrentUser(shNULL);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void OnUserChanged(ShUser * pUser)
{
	// not used ...
}
