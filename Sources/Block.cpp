#include "StdAfx.h"

Block::Block(ShPrefab * prefab)
: m_pBlockPref(prefab)
, m_bShow(true)
, m_pBlockEntity(shNULL)
{
	CShArray<ShObject *> prefabElm;
	ShPrefab::GetChildArray(m_pBlockPref, prefabElm);

	CShVector2 toto = ShPrefab::GetPosition2(m_pBlockPref);

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