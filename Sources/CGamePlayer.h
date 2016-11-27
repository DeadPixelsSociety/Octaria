//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGamePlayer.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CGAMEPLAYER_H
#define __CGAMEPLAYER_H

class CGamePoulpe;

//
class CGamePlayer
{

public:
	
	explicit			CGamePlayer				(void);
	virtual				~CGamePlayer			(void);

	void				Initialize				(void);
	void				Release					(void);

	void				AddObjectToIventory		(EBlocType blocValue);

	void				AddPoulpeToList			(CGamePoulpe * pPoulpe);

	CGamePoulpe *		GetPoulpeToPlay			(void);

protected:

private:

public:

protected:

private:

	CShArray<CGamePoulpe *>	m_aPoulpeList;
	int						m_IdpoulpeToPlay;

	CShArray<EBlocType>		m_aInventory;
		
};

#endif // __CGAMEPLAYER_H
