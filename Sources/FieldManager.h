//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : FieldManager.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef __FIELDMANAGER__H
#define __FIELDMANAGER__H

typedef struct 
{
	int x, y, value;
}MAPPROC;

#include "ProceduralGeneration.h"

/*
	20-50	: Pierre
	50-70	: Herbe
	70-100	: Terre
	100-130	: Charbon

	Reste	: Vide
*/

class FieldManager
{
public:

	FieldManager	(const CShVector2 & size);
	~FieldManager	();

	void						GetFieldBlockType	(CShArray<EBlocValue> & aFieldValues);
	void						GetFieldCoord		(CShArray<CShVector2> & aFieldCoord);

private:

	void						GenerateMap		(void);	// Genere procéduralement la map 

private:

	ProceduralGeneration *		m_pGenerator;		// Classe qui gere la generation procédurale
	CShVector2					m_csMapSize;		// Taille de la map contenant les valeurs de la generation procedurale
	MAPPROC **					m_csMap;			// Map contenant les valeurs de la generation procedurale

	int							m_iStep;			// Parametre "pas" de la generation procedurale
	int							m_iOctave;			// Parametre "octave" de la generation procédurale

};

#endif	//__FIELDMANAGER__H