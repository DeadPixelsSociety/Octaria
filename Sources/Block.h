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


	void				Initialize		(ShPrefab * pPrefab, EBlocType blocType, b2World * pWorld);
	void				Release			(b2World * pWorld);

	bool				HitByPlayer		(void);

	const CShVector2 &	GetPosition		(void);

	float				GetWidth		(void);
	float				GetHeight		(void);

	ShEntity2 *			GetEntity		(void);

	EBlocType			GetType			(void);

private:
	void				CreateBlocBody	(b2World * pWorld);

private:

	//Prefab et entité 2d
	ShPrefab		*		m_pBlockPref;
	ShEntity2		*		m_pBlockEntity;

	//Coordonnees(concrete, à l'écran), Coordonnées(Abstraite, dans un tableau), Taille et visibilité
	CShVector2				m_v2Position;
	CShVector2				m_v2AbstractPosition;
	CShVector2				m_v2Size;

	//Valeur dans lesquels le block est genéré
	int						m_iStartV;
	int						m_iEndV;

	EBlocType				m_eBlocType;

	int						m_blockLife;

	b2Body *				m_pBody;

};

#endif //__BLOCK__H