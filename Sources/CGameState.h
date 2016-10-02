//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameState.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CGAMESTATE_H
#define __CGAMESTATE_H

//
class CGameState
{

public:
	

	//
	// Construction / Destruction
	explicit		CGameState		(void);
	virtual			~CGameState		(void);

	//
	// Initialization / Release / Activation / Deactivation
	virtual void	Initialize		(void) = 0;
	virtual void	Release			(void) = 0;
	virtual void	Activate		(void) = 0;
	virtual void	DeActivate		(void) = 0;

	//
	// Update
	virtual void	Update			(float deltaTimeInMs) = 0;

	//
	// Events
	virtual void	OnTouchDown		(int iTouch, float positionX, float positionY) = 0;
	virtual void	OnTouchUp		(int iTouch, float positionX, float positionY) = 0;
	virtual void	OnTouchMove		(int iTouch, float positionX, float positionY) = 0;

protected:
	
	float			computeVecteurNorme(float Ax, float Ay, float Bx, float By);

private:

public:

protected:

private:
};

#endif // __CGAMESTATE_H
