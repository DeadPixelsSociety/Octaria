//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGameStateManager.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CGAMESTATEMANAGER_H
#define __CGAMESTATEMANAGER_H

//
/// Pinball game state manager
class CGameStateManager
{
public:

	//
	/// @todo comment
	enum EGameState
	{
		e_game_state_main_menu,
		e_game_state_game,
		e_game_state_max,
	};

	//
	// Construction / Destruction
	explicit				CGameStateManager					(void);
	virtual					~CGameStateManager					(void);

	//
	// Initialization / Release
	void					Initialize							(void);
	void					Release								(void);

	//
	// Update
	void					Update								(float deltaTimeInMs);

	//
	// Game state access
	void					Push								(EGameState eGameState);
	void					Pop									(void);
	CGameState *			GetCurrentGameState					(void);

	//
	// Events
	virtual void			OnTouchDown							(int iTouch, float positionX, float positionY);
	virtual void			OnTouchUp							(int iTouch, float positionX, float positionY);
	virtual void			OnTouchMove							(int iTouch, float positionX, float positionY);

protected:

private:

public:

protected:

private:

	CGameState *			m_apGameState[e_game_state_max];	///< @todo comment
	CShStack<CGameState*>	m_sGameState;						///< @todo comment

};

extern CGameStateManager g_gameStateManager;

#endif // __CGAMESTATEMANAGER_H
