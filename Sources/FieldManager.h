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

class FieldManager
{
public:

	FieldManager	(const CShVector2 & size);
	~FieldManager	();

	void						GetFieldBlockType		(CShArray<EBlocValue> & aFieldValues);
	void						GetFieldCoord			(CShArray<CShVector2> & aFieldCoord);

private:

	void						GenerateMap				(void);	// Genere proc�duralement la map 

private:

	ProceduralGeneration *		m_pGenerator;		// Classe qui gere la generation proc�durale
	CShVector2					m_csMapSize;		// Taille de la map contenant les valeurs de la generation procedurale
	MAPPROC **					m_csMap;			// Map contenant les valeurs de la generation procedurale

	int							m_iStep;			// Parametre "pas" de la generation procedurale
	int							m_iOctave;			// Parametre "octave" de la generation proc�durale

	int							m_magnitude;		// Magnitude � appliquer pour passer de l'intervalle [0-1] � des valeurs utilisables plus simplement

};

#endif	//__FIELDMANAGER__H