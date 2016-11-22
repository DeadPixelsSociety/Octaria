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

	explicit		FieldManager		(const CShVector2 & size);
	virtual			~FieldManager		();

	void			Initialize			(bool is1D);
	void			Release				(void);
		
	void			GetFieldBlockType	(CShArray<EBlocType> & aFieldType);
	void			GetFieldCoord		(CShArray<CShVector2> & aFieldCoord);

	void			GenerateMap			(void);

	void			MergeMap			(const CShArray<EBlocType> & aFieldType, CShArray<EBlocType> & aRes);

private:

	void			GetFieldBlockValue	(CShArray<int> & aFieldType);

	void			GenerateMap1D		(void);
	void			GenerateMap2D		(void);	

private:

	ProceduralGeneration *		m_pGenerator;		// Classe qui gere la generation procédurale
	CShVector2					m_csMapSize;		// Taille de la map contenant les valeurs de la generation procedurale
	MAPPROC **					m_csMap;			// Map contenant les valeurs de la generation procedurale

	int							m_iStep;			// Parametre "pas" de la generation procedurale
	int							m_iOctave;			// Parametre "octave" de la generation procédurale

	int							m_magnitude;		// Magnitude à appliquer pour passer de l'intervalle [0-1] à des valeurs utilisables plus simplement

	bool						m_is1D;

};

#endif	//__FIELDMANAGER__H