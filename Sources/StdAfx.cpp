//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : StdAfx.cpp
// Author      : PRADAL & co
// Description : -
// Platform    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void SetCurrentUser(ShUser * pUser)
{
	// TODO
	if (shNULL != pUser) // login
	{
		g_pCurrentUser = pUser;
	}
	else if (shNULL != g_pCurrentUser) // logout
	{
		g_pCurrentUser = shNULL;
	}
	else
	{
		SH_ASSERT_ALWAYS();
	}
}
