//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateMainMenu.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CGameStateMainMenu_H
#define __CGameStateMainMenu_H


//
/// Level game state
class CGameStateMainMenu : public CGameState
{
public:

	enum EState
	{
		e_state_enter,
		e_state_playing,
		e_state_end,
	};

	//
	// Construction / Destruction
	explicit			CGameStateMainMenu	(void);
	virtual				~CGameStateMainMenu	(void);

		//
	// Initialization / Release / Activation / Deactivation
	virtual void			Initialize			(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			Release				(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			Activate			(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			DeActivate			(void) SH_ATTRIBUTE_OVERRIDE;
	//
	// Update
	virtual void			Update				(float deltaTimeInMs) SH_ATTRIBUTE_OVERRIDE;

	virtual void			OnTouchDown			(int iTouch, float positionX, float positionY) SH_ATTRIBUTE_OVERRIDE;
	virtual void			OnTouchUp			(int iTouch, float positionX, float positionY) SH_ATTRIBUTE_OVERRIDE;
	virtual void			OnTouchMove			(int iTouch, float positionX, float positionY) SH_ATTRIBUTE_OVERRIDE;

protected:

private:


public:

protected:

private:
	EState				m_eState;

	ShEntity2 *			m_pCreatedPoulpe;
};

#endif // __CGameStateMainMenu_H
