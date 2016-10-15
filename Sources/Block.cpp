#include "StdAfx.h"

Block::Block(ShPrefab * prefab)
	: m_pBlockPref(prefab)
	, m_bShow(false)
	, m_pBlockEntity(shNULL)
{
	CShArray<ShObject *> prefabElm;
	ShPrefab::GetChildArray(m_pBlockPref, prefabElm);

	CShVector2 toto = ShPrefab::GetPosition2(m_pBlockPref);

	

	for (int i = 0; i < prefabElm.GetCount(); ++i)
	{
		//Si l'element actuel est le sprite 2D, on le recupere
		if (ShObject::GetType(prefabElm[i]) == ShObject::e_type_entity2)
		{
			//Recuperation des informations de level et d'entite éd
			CShIdentifier poolid = ShObject::GetPoolIdentifier(prefabElm[i]);
			CShIdentifier id = ShObject::GetIdentifier(prefabElm[i]);

			//Creation de l'entite 2D
			m_pBlockEntity = ShEntity2::Create(poolid, GID(NULL), GID(layer_default), CShIdentifier("octaria"), id, CShVector3(-100.0f, -100.0f, 1.0f), CShEulerAngles(), CShVector3(5.0f, 5.0f, 1.0f));
			SH_ASSERT(shNULL != m_pBlockEntity);
			
			//Parsing du dataset
			int dataSetCount = ShObject::GetDataSetCount(prefabElm[i]);
			for (int j = 0; j < dataSetCount; ++j)
			{
				ShDataSet * current_ds = ShObject::GetDataSet(prefabElm[i], j);
				int nb_data = ShDataSet::GetDataCount(current_ds);
				for (int k = 0; k < nb_data; ++k)
				{
					ShDataSet::EDataType current_type = ShDataSet::GetDataType(current_ds, k);
					CShIdentifier c_id;


					switch (current_type)
					{
						//Recuperation des valeurs de type int
						case ShDataSet::e_data_type_int:
							c_id = ShDataSet::GetDataIdentifier(current_ds, k);

							//Si valeur representant la borne inferrieur de generation procedurale
							if (c_id == CShIdentifier("fgenerations"))
								ShDataSet::GetDataValue(current_ds, k, m_iStartV);

							//Si valeur representant la borne supperieur de generation procedurale
							if (c_id == CShIdentifier("fgeneratione"))
								ShDataSet::GetDataValue(current_ds, k, m_iEndV);
							break;

						default:
							break;
					}
				}

				

				int sortie;
				bool tetest = ShDataSet::GetDataValue(ShObject::GetDataSet(prefabElm[i], j), 1, sortie);
				int yolo = 0;
			}
			
			int t = 0;
		}
	}
	

	int size = prefabElm.GetCount();
}
void Block::setPosition(CShVector2 position)
{
	m_v2Position = position;
}

void Block::setPosition(int x, int y)
{
	m_v2Position = CShVector2(x, y);
}

void Block::Update()
{
	ShEntity2::SetWorldPosition2(m_pBlockPref, m_v2Position.m_x, m_v2Position.m_y);
	ShEntity2::SetShow(m_pBlockEntity, m_bShow);
}