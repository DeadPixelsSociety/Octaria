//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CMultiResolutionApplication.cpp
// Author      : PRADAL & co
// Description : -
// Platform    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CMultiResolutionApplication::CMultiResolutionApplication(void)
: m_pCamera(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ CMultiResolutionApplication::~CMultiResolutionApplication(void)
{

} 

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnPreInitialize(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnPostInitialize(void)
{
	ShLevel::Load(CShIdentifier("level_zelda_1"));
	g_gameStateManager.Initialize();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnPreUpdate(float deltaTimeInMs)
{
	g_gameStateManager.Update(deltaTimeInMs);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnPostUpdate(float deltaTimeInMs)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnPreRelease(void)
{
	g_gameStateManager.Release();
	ShLevel::Release();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnPostRelease(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnActivate(void)
{
	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnDeactivate(void)
{
	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnTouchDown(int iTouch, float positionX, float positionY)
{
	g_gameStateManager.OnTouchDown(iTouch, positionX, positionY);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnTouchUp(int iTouch, float positionX, float positionY)
{
	g_gameStateManager.OnTouchUp(iTouch, positionX, positionY);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::OnTouchMove(int iTouch, float positionX, float positionY)
{
	g_gameStateManager.OnTouchMove(iTouch, positionX, positionY);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
ShCamera * CMultiResolutionApplication::GetCamera(void)
{
	return(m_pCamera);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CMultiResolutionApplication::SetCamera(ShCamera * pCamera)
{
	m_pCamera = pCamera;
}