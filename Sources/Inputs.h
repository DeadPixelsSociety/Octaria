//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : Inputs.h
// Author      : PRADAL & co
// Platform    : All
// Description : Input handle
//--------------------------------------------------------------------------------------------------

#ifndef __OCTARIA_INPUTS_H
#define __OCTARIA_INPUTS_H

class Inputs
{
public:
	explicit	 Inputs				(void);
	virtual		~Inputs				(void);

	void		Initialize			(ShUser * pUser);
	void		Release				(void);

	void		Update				(void);

	bool		IsLeftPressed		(void);
	bool		IsRightPressed		(void);
	bool		IsUpPressed			(void);
	bool		IsDownPressed		(void);
	bool		IsJumpPressed		(void);

private:

	ShUser * m_pUser;

	bool m_bLeft;
	bool m_bRight;
	bool m_bUp;
	bool m_bDown;
	bool m_bJump;
};

#endif // __OCTARIA_INPUTS_H