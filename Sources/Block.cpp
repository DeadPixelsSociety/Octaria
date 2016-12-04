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
, m_iStartV(0)
, m_iEndV(0)
, m_v2Position()
, m_pBody(shNULL)
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
void Block::Initialize(ShPrefab * pPrefab, EBlocType blocType, b2World * pWorld)
{
	//TODO remove prefab use ? 

	m_pBlockPref = pPrefab;
	CShArray<ShObject *> aPrefabElm;
	ShPrefab::GetChildArray(m_pBlockPref, aPrefabElm);

	int nChildCount = aPrefabElm.GetCount();
	for (int iChild = 0; iChild < nChildCount; ++iChild)
	{
		//Si l'element actuel est le sprite 2D, on le recupere
		if (ShObject::GetType(aPrefabElm[iChild]) == ShObject::e_type_entity2)
		{
			m_pBlockEntity = (ShEntity2 *)aPrefabElm[iChild];
			m_v2Position = ShEntity2::GetWorldPosition2(m_pBlockEntity);
		}
	}

	m_eBlocType = blocType;
	switch (m_eBlocType)
	{
		case e_bloc_herbe: m_blockLife = 3; break;
		case e_bloc_terre: m_blockLife = 5; break;
		case e_bloc_pierre: m_blockLife = 10; break;
		case e_bloc_charbon: m_blockLife = 12; break;
		default: m_blockLife = 0;
	}

	if (e_bloc_vide != m_eBlocType)
	{
		CreateBlocBody(pWorld);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Block::Release(b2World * pWorld)
{
	pWorld->DestroyBody(m_pBody);

	m_pBlockPref = shNULL;
	m_pBlockEntity = shNULL;
	m_pBody = shNULL;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
bool Block::HitByPlayer(void)
{
	--m_blockLife;

	// set sprite depend to life

	return(!m_blockLife);
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
	return(ShEntity2::GetWidth(m_pBlockEntity));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
float Block::GetHeight(void)
{
	return(ShEntity2::GetHeight(m_pBlockEntity));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
ShEntity2 * Block::GetEntity(void)
{
	return(m_pBlockEntity);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
EBlocType Block::GetType(void)
{
	return(m_eBlocType);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Block::CreateBlocBody(b2World * pWorld)
{
	b2BodyDef blockDef;
	blockDef.type = b2_staticBody;
	blockDef.allowSleep = true;

	b2Vec2 blockPos = ConvertShineToBox2D(m_v2Position);
	blockDef.position.Set(blockPos.x, blockPos.y);
	m_pBody = pWorld->CreateBody(&blockDef);
	b2PolygonShape polyShape;
	b2Vec2 blockSize = ConvertShineToBox2D(CShVector2(31.0f, 31.0f));
	polyShape.SetAsBox(blockSize.x, blockSize.y);

	b2FixtureDef dynaFixtureBlock;
	dynaFixtureBlock.shape = &polyShape;
	dynaFixtureBlock.density = 5.0f; // densité*aire = masse
	dynaFixtureBlock.friction = 0.1f;
	dynaFixtureBlock.restitution = 0.1f;
	m_pBody->CreateFixture(&dynaFixtureBlock);
}
