//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : Block.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __BLOCK__H
#define __BLOCK__H

class Block
{
public:

	explicit	Block	(void);
	virtual		~Block	(void);


	void				Initialize		(ShPrefab * pPrefab);
	void				Release			(void);

	void				SetPosition		(const CShVector2 & position);

	const CShVector2 &	GetPosition		(void);

	float				GetWidth		(void);
	float				GetHeight		(void);

private:

	//Prefab et entit� 2d
	ShPrefab		*		m_pBlockPref;
	ShEntity2		*		m_pBlockEntity;

	//Coordonnees(concrete, � l'�cran), Coordonn�es(Abstraite, dans un tableau), Taille et visibilit�
	CShVector2				m_v2Position;
	CShVector2				m_v2AbstractPosition;
	CShVector2				m_v2Size;
	bool					m_bShow;

	//Valeur dans lesquels le block est gen�r�
	int						m_iStartV;
	int						m_iEndV;

};

#endif //__BLOCK__H