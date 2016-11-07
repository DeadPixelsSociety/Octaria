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
, m_iStep(8)
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
	int width = m_csMapSize.m_x;
	int height = m_csMapSize.m_y;

	for (int x = 0; x < width; ++x)
	{
		// generate stone curve
		int stone = m_pGenerator->Noise(x, 0, 1, 25);
		stone +=	m_pGenerator->Noise(x, 0, 1, 20);
		stone +=	5;

		// generate dirt curve
		int dirt =	m_pGenerator->Noise(x, 0, 1, 28);
		dirt +=		m_pGenerator->Noise(x, 0, 1, 25);
		dirt +=		5;

		for (int y = 0; y < height; ++y)
		{
			m_csMap[x][y].x = x;
			m_csMap[x][y].y = y;

			// fill all column blocks
			if (y < stone) 
			{
				m_csMap[x][y].value = 3;
			
				//int val;
				//val = m_pGenerator->Noise(x, y, 1, 14);
				//if (10 < val) 
				//{
				//	m_csMap[x][y].value = 2;
				//}
				
				//val = m_pGenerator->Noise(x, y * 2, 1, 12);
				//if (10 < val) 
				//{
				//	m_csMap[x][y].value = 0;
				//}
			}
			else if (y < dirt) 
			{
				m_csMap[x][y].value = 2;
			}
			else
			{
				m_csMap[x][y].value = 0;
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
			aFieldValues.Add((EBlocValue)idBloc);
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
