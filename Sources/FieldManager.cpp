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
FieldManager::FieldManager(CShVector2 size)
: m_csMapSize(size)
, m_iStep(10)
, m_iOctave(10)
{
	m_pgGenerater = new ProceduralGeneration(m_csMapSize.m_x + 1, m_csMapSize.m_y + 1, m_iStep, m_iOctave);

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
			m_csMap[x][y].value = (int)(m_pgGenerater->fonction_bruit2D(m_csMap[x][y].x, m_csMap[x][y].y) * 255);
		}
	}
}
