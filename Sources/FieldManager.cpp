//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : FieldManager.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h";

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
FieldManager::FieldManager(const CShVector2 & size)
: m_csMapSize(size)
, m_iStep(10)
, m_iOctave(10)
{
	m_pGenerator = new ProceduralGeneration(m_csMapSize.m_x + 1, m_csMapSize.m_y + 1, m_iStep, m_iOctave);

	//Creation du tableau 2D
	m_csMap = new MAPPROC*[m_csMapSize.m_x];

	for (int i = 0; i < m_csMapSize.m_x; ++i)
	{
		m_csMap[i] = new MAPPROC[m_csMapSize.m_y];
	}

	//Remplissage de la map
	GenerateMap();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
FieldManager::~FieldManager()
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GenerateMap(void)
{
	for (int x = 0; x < m_csMapSize.m_x; ++x)
	{
		for (int y = 0; y < m_csMapSize.m_y; ++y)
		{
			//Assignation des valeurs pour le positionnement
			m_csMap[x][y].x = x;
			m_csMap[x][y].y = y;

			//Recuperation d'une valeur lisse
			m_csMap[x][y].value = (int)(m_pGenerator->fonction_bruit2D(x, y) * 255);
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GetFieldBlockType(CShArray<EBlocValue> & aFieldValues)
{
	for (int x = 0; x < m_csMapSize.m_x; ++x)
	{
		for (int y = 0; y < m_csMapSize.m_y; ++y)
		{
			int idBloc = m_csMap[x][y].value;

			if (idBloc >= 20 && idBloc < 50)
			{
				aFieldValues.Add(e_bloc_pierre);
			}
			else if (idBloc >= 50 && idBloc < 70)
			{
				aFieldValues.Add(e_bloc_herbe);
			}
			else if (idBloc >= 70 && idBloc < 100)
			{
				aFieldValues.Add(e_bloc_terre);
			}
			else if (idBloc >= 100 && idBloc < 130)
			{
				aFieldValues.Add(e_bloc_charbon);
			}
			else
			{
				aFieldValues.Add(e_bloc_vide);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GetFieldCoord(CShArray<CShVector2> & aFieldCoord)
{
	for (int x = 0; x < m_csMapSize.m_x; ++x)
	{
		for (int y = 0; y < m_csMapSize.m_y; ++y)
		{
			aFieldCoord.Add(CShVector2(m_csMap[x][y].x, m_csMap[x][y].y));
		}
	}
}
