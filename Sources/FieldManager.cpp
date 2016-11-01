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
, m_magnitude(255)
, m_iStep(10)
, m_iOctave(10)
{
	m_pGenerator = new ProceduralGeneration(m_csMapSize.m_x + 1, m_csMapSize.m_y + 1, m_iStep, m_iOctave);
	m_pGenerator->Initialize(true);

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
	int height = m_csMapSize.m_x;
	int width = m_csMapSize.m_y;

	for (int x = 0; x < height; ++x)
	{
		// generate rock curve
		int stone = m_pGenerator->Noise(x, 0, 1, 10);
		stone +=	m_pGenerator->Noise(x, 0, 1, 20);
		stone +=	m_pGenerator->Noise(x, 0, 1, 5);

		// generate dirt curve
		int dirt =	m_pGenerator->Noise(x, 0, 1, 22);
		dirt +=		m_pGenerator->Noise(x, 0, 1, 18);

		for (int y = 0; y < width; ++y)
		{
			m_csMap[x][y].x = x;
			m_csMap[x][y].y = y;

			// fill all column blocks
			if (y < stone) 
			{
				m_csMap[x][y].value = 175;
			}
			else if (y < dirt) 
			{
				m_csMap[x][y].value = 100;
			}
			else
			{
				m_csMap[x][y].value = 250;
			}
		}
	}
}
//{
//	for (int x = 0; x < m_csMapSize.m_x; ++x)
//	{
//		for (int y = 0; y < m_csMapSize.m_y; ++y)
//		{
//			//Assignation des valeurs pour le positionnement
//			m_csMap[x][y].x = x;
//			m_csMap[x][y].y = y;
//
//			//Recuperation d'une valeur lisse
//			m_csMap[x][y].value = (int)(m_pGenerator->fonction_bruit2D(x, y) * m_magnitude);
//		}
//	}
//}

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

			if (idBloc >= 0 && idBloc < 80)
			{
				aFieldValues.Add(e_bloc_herbe);
			}
			else if (idBloc >= 80 && idBloc < 150)
			{
				aFieldValues.Add(e_bloc_terre);
			}
			else if (idBloc >= 150 && idBloc < 200)
			{
				aFieldValues.Add(e_bloc_pierre);
			}
			//else if (idBloc >= 100 && idBloc < 130)
			//{
			//	aFieldValues.Add(e_bloc_charbon);
			//}
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
