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
void FieldManager::Initialize(bool is1D)
{
	m_is1D = is1D;

	m_pGenerator = new ProceduralGeneration(m_csMapSize.m_x + 1, m_csMapSize.m_y + 1, m_iStep, m_iOctave);
	m_pGenerator->Initialize(m_is1D);

	//Creation du tableau 2D
	m_csMap = new MAPPROC*[m_csMapSize.m_x];

	for (int i = 0; i < m_csMapSize.m_x; ++i)
	{
		m_csMap[i] = new MAPPROC[m_csMapSize.m_y];
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::Release(void)
{
	SH_SAFE_DELETE_ARRAY(m_csMap);

	m_pGenerator->Release();
	SH_SAFE_DELETE(m_pGenerator);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GenerateMap()
{
	//Remplissage de la map
	if (m_is1D)
	{
		GenerateMap1D();
	}
	else
	{
		GenerateMap2D();
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::MergeMap(const CShArray<EBlocType>& aFieldType, CShArray<EBlocType>& aRes)
{
	CShArray<int> aCurrentFieldValues;
	GetFieldBlockValue(aCurrentFieldValues);

	SH_ASSERT(aFieldType.GetCount() == aCurrentFieldValues.GetCount());

	int nBlockCount = aFieldType.GetCount();
	for (int i = 0; i < nBlockCount; ++i)
	{
		if (e_bloc_pierre == aFieldType[i])
		{
			if (190 <= aCurrentFieldValues[i])
			{
				aRes.Add(e_bloc_vide);
			}
			else
			{
				aRes.Add(e_bloc_pierre);
			}
		}
		else
		{
			aRes.Add(aFieldType[i]);
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GenerateMap1D(void)
{
	int width = m_csMapSize.m_x;
	int height = m_csMapSize.m_y;

	for (int x = 0; x < width; ++x)
	{
		// generate stone curve
		int stone = m_pGenerator->Noise(x, 0, 1, 25);
		stone +=	m_pGenerator->Noise(x, 0, 1, 20);
		stone +=	3;

		// generate dirt curve
		int dirt =	m_pGenerator->Noise(x, 0, 1, 28);
		dirt +=		m_pGenerator->Noise(x, 0, 1, 25);
		dirt +=		3;

		for (int y = 0; y < height; ++y)
		{
			m_csMap[x][y].x = x;
			m_csMap[x][y].y = y;

			// fill all column blocks
			if (y < stone) 
			{
				m_csMap[x][y].value = 3;
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

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GenerateMap2D(void)
{
	for (int x = 0; x < m_csMapSize.m_x; ++x)
	{
		for (int y = 0; y < m_csMapSize.m_y; ++y)
		{
			//Assignation des valeurs pour le positionnement
			m_csMap[x][y].x = x;
			m_csMap[x][y].y = y;
	
			//Recuperation d'une valeur lisse
			m_csMap[x][y].value = m_pGenerator->Noise(x, y, 1, m_magnitude);
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GetFieldBlockType(CShArray<EBlocType> & aFieldType)
{
	for (int x = 0; x < m_csMapSize.m_x; ++x)
	{
		for (int y = 0; y < m_csMapSize.m_y; ++y)
		{
			int idBloc = m_csMap[x][y].value;
			aFieldType.Add((EBlocType)idBloc);
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


//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void FieldManager::GetFieldBlockValue(CShArray<int> & aFieldType)
{
	for (int x = 0; x < m_csMapSize.m_x; ++x)
	{
		for (int y = 0; y < m_csMapSize.m_y; ++y)
		{
			aFieldType.Add(m_csMap[x][y].value);
		}
	}
}