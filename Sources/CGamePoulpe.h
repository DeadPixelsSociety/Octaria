//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGamePoulpe.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CGAMEPOULPE_H
#define __CGAMEPOULPE_H

//
class CGamePoulpe
{

public:
	
	enum EPoulpeState
	{
		e_state_init,		
		e_state_idle,	
		e_state_playing,
		e_state_dead,
	};

	explicit			CGamePoulpe			(void);
	virtual				~CGamePoulpe		(void);

	void				Initialize			(CShIdentifier levelIdentifier, b2World * pWorld);
	void				Release				(void);

	void				Update				(bool isLeft, bool isRight, bool isDown, bool isUp);

	void				SetLook				(float cursorX, float cursorY);

	const CShVector2 	GetPosition			() const;

	const EPoulpeLook & GetLook				() const;

	void				TakeDamage			(int damage);

protected:

private:

	void				UpdateFromInputs	(bool isLeft, bool isRight, bool isDown, bool isUp);

public:

protected:

private:

	EPoulpeState			m_eState;

	EPoulpeLook				m_look;

	CShArray<ShEntity2 *>	m_aPoulpeAnimation[2];	// Walk animation sprite array, left and right
	int						m_direction;			// 0: left, 1: right	
	int						m_currentId;			// current displayed sprite (0..4)
	int						m_tempoAnim;		

	int						m_life;

	b2World *				m_pWorld;
	b2Body *				m_pBody;
};

#endif // __CGAMEPOULPE_H
