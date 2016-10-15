#include "StdAfx.h"

Block::Block(ShPrefab * prefab)
	: m_pBlockPref(prefab)
	, m_bShow(true)
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
			CShIdentifier poolid = ShObject::GetPoolIdentifier(prefabElm[i]);
			CShIdentifier id = ShObject::GetIdentifier(prefabElm[i]);
			m_pBlockEntity = ShEntity2::Create(poolid, GID(NULL), GID(layer_default), CShIdentifier("octaria"), id, CShVector3(-100.0f, -100.0f, 1.0f), CShEulerAngles(), CShVector3(5.0f, 5.0f, 1.0f));
			SH_ASSERT(shNULL != m_pBlockEntity);
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
}