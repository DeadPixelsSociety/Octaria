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
void Block::Release(void)
{
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
	b2BodyDef playerDef;
	playerDef.type = b2_staticBody;
	playerDef.allowSleep = true;

	playerDef.position.Set(0, 0);
	m_pBody = pWorld->CreateBody(&playerDef);
	b2PolygonShape polyShape;
	polyShape.SetAsBox(64.0f, 64.0f); // FIXME

	b2FixtureDef dynaFixturePlayer;
	dynaFixturePlayer.shape = &polyShape;
	dynaFixturePlayer.density = 0.1f; // densité*aire = masse
	dynaFixturePlayer.friction = 0.3f;
	dynaFixturePlayer.restitution = 0.3f;
	m_pBody->CreateFixture(&dynaFixturePlayer);
}
