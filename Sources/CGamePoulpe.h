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

	explicit		CGamePoulpe		(void);
	virtual			~CGamePoulpe	(void);

	void			Initialize		(CShIdentifier levelIdentifier);
	void			Release			(void);

	void			Update			(bool isLeft, bool isRight);

protected:

private:

	void			UpdateFromInputs(bool isLeft, bool isRight);

public:

protected:

private:

	EPoulpeState			m_eState;

	CShArray<ShEntity2 *>	m_aPoulpeAnimation[2];	// Walk animation sprite array, left and right
	int						m_direction;			// 0: left, 1: right	
	int						m_currentId;			// current displayed sprite (0..4)
	int						m_tempoAnim;			
};

#endif // __CGAMEPOULPE_H
