//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGamePlayer.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CGAMEPLAYER_H
#define __CGAMEPLAYER_H

class CPoulpe;

//
class CGamePlayer
{

public:
	
	explicit			CGamePlayer				(void);
	virtual				~CGamePlayer			(void);

	void				Initialize				(void);
	void				Release					(void);

	void				AddObjectToIventory		(EBlocValue blocValue);

protected:

private:

public:

protected:

private:

	CShArray<CPoulpe *>		m_aPlayerList;
	CShArray<EBlocValue>	m_aInventory;
		
};

#endif // __CGAMEPLAYER_H
