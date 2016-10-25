//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : Block.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
Block::Block(void)
: m_pBlockPref(shNULL)
, m_pBlockEntity(shNULL)
, m_bShow(false)
, m_iStartV(0)
, m_iEndV(0)
, m_v2Position()
{
	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
Block::~Block(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Block::Release(void)
{
	m_pBlockPref = shNULL;
	m_pBlockEntity = shNULL;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Block::Initialize(ShPrefab * pPrefab)
{
	m_pBlockPref = pPrefab;
	CShArray<ShObject *> aPrefabElm;
	ShPrefab::GetChildArray(m_pBlockPref, aPrefabElm);

	int nChildCount = aPrefabElm.GetCount();
	for (int i = 0; i < nChildCount; ++i)
	{
		//Si l'element actuel est le sprite 2D, on le recupere
		if (ShObject::GetType(aPrefabElm[i]) == ShObject::e_type_entity2)
		{
			m_pBlockEntity = (ShEntity2 *)aPrefabElm[i];

			//Parsing du dataset
			int dataSetCount = ShObject::GetDataSetCount(m_pBlockEntity);

			for (int j = 0; j < dataSetCount; ++j)
			{
				ShDataSet * current_ds = ShObject::GetDataSet(m_pBlockEntity, j);
				int nb_data = ShDataSet::GetDataCount(current_ds);

				for (int k = 0; k < nb_data; ++k)
				{
					ShDataSet::EDataType current_type = ShDataSet::GetDataType(current_ds, k);
					CShIdentifier c_id;

					switch (current_type)
					{
						//Recuperation des valeurs de type int
						case ShDataSet::e_data_type_int:
						{
							c_id = ShDataSet::GetDataIdentifier(current_ds, k);

							//Si valeur representant la borne inferrieur de generation procedurale
							if (c_id == CShIdentifier("fgenerations"))
							{
								ShDataSet::GetDataValue(current_ds, k, m_iStartV);
							}

							//Si valeur representant la borne supperieur de generation procedurale
							if (c_id == CShIdentifier("fgeneratione"))
							{
								ShDataSet::GetDataValue(current_ds, k, m_iEndV);
							}
						}
						break;
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Block::SetPosition(const CShVector2 & position)
{
	m_v2Position = position;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
const CShVector2 & Block::GetPosition()
{
	return(m_v2Position);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
float Block::GetWidth(void)
{
	return ShEntity2::GetWidth(m_pBlockEntity);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
float Block::GetHeight(void)
{
	return ShEntity2::GetHeight(m_pBlockEntity);
}
