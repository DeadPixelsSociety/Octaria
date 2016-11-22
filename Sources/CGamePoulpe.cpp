//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGamePoulpe.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"
extern ShCamera * g_pCamera;
//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGamePoulpe::CGamePoulpe(void)
: m_eState(e_state_init)
, m_currentId(0)
, m_tempoAnim(0)
, m_direction(0)
, m_life(100)
, m_pBody(shNULL)
, m_pWorld(shNULL)
{
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ CGamePoulpe::~CGamePoulpe(void)
{
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::Release(void)
{
	for (int i = 0; i < 2; ++i)
	{
		int nSprite = m_aPoulpeAnimation[i].GetCount();
		for (int iSprite = 0; i < nSprite; ++iSprite)
		{
			m_aPoulpeAnimation[i][nSprite] = shNULL;
		}
		m_aPoulpeAnimation[i].Empty();
	}

	m_pBody = shNULL;
	m_pWorld = shNULL;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::Initialize(CShIdentifier levelIdentifier, b2World * pWorld)
{
	m_direction = 0;
	m_currentId = 0;
	m_tempoAnim = 0;

	m_pWorld = pWorld;

	//
	// Sprites
	char spriteName[256];
	char spriteIdent[256];

	for (int i = 0; i < 5; i++)
	{
		sprintf(spriteName, "sprite_octaria_poulpe_left_%d", i);
		sprintf(spriteIdent, "poulpe_left_%d", i);
		ShEntity2 * pEntity = ShEntity2::Create(levelIdentifier, CShIdentifier(spriteName), CShIdentifier("layer_default"), CShIdentifier("octaria"), CShIdentifier(spriteIdent), CShVector3(0.0f, 0.0f, 4.0f), CShEulerAngles(), CShVector3(0.5f, 0.5f, 1.0f), false);
		SH_ASSERT(shNULL != pEntity);
		m_aPoulpeAnimation[0].Add(pEntity);
	}
	ShEntity2::SetShow(m_aPoulpeAnimation[0][0], true);

	for (int i = 0; i < 5; i++)
	{
		sprintf(spriteName, "sprite_octaria_poulpe_right_%d", i);
		sprintf(spriteIdent, "poulpe_right_%d", i);
		ShEntity2 * pEntity = ShEntity2::Create(levelIdentifier, CShIdentifier(spriteName), CShIdentifier("layer_default"), CShIdentifier("octaria"), CShIdentifier(spriteIdent), CShVector3(0.0f, 0.0f, 4.0f), CShEulerAngles(), CShVector3(0.5f, 0.5f, 1.0f), false);
		SH_ASSERT(shNULL != pEntity);
		m_aPoulpeAnimation[1].Add(pEntity);
	}

	//
	// Box2D
	b2BodyDef playerDef;
	playerDef.type = b2_dynamicBody;
	playerDef.allowSleep = false;
	
	playerDef.position.Set(0, 0);
	m_pBody = m_pWorld->CreateBody(&playerDef);
	b2PolygonShape polyShape;
	polyShape.SetAsBox(60.0f, 60.0f); // FIXME
	
	b2FixtureDef dynaFixturePlayer;
	dynaFixturePlayer.shape = &polyShape;
	dynaFixturePlayer.density = 0.1f; // densité*aire = masse
	dynaFixturePlayer.friction = 0.3f;
	dynaFixturePlayer.restitution = 0.3f;
	m_pBody->CreateFixture(&dynaFixturePlayer);

	m_eState = e_state_init;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::Update(bool isLeft, bool isRight, bool isDown, bool isUp)
{
	switch (m_eState)
	{
		case e_state_init:
		{ 
			m_direction = 0;
			m_currentId = 0;	
			m_tempoAnim = 0;
			m_eState = e_state_playing;
		}
		break;
	
		case e_state_idle:
		{

		}
		break;

		case e_state_playing:
		{
			UpdateFromInputs(isLeft, isRight, isDown, isUp);
		}
		break;

		case e_state_dead:
		{

		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::SetLook(float cursorX, float cursorY)
{
	CShVector3 currentPos3 = ShEntity2::GetWorldPosition(m_aPoulpeAnimation[m_direction][m_currentId]);
	CShVector2 currentPos2 = ShCamera::Project(g_pCamera, currentPos3);
	float dirDegree = atan2((cursorX + 640) - currentPos2.m_x, (cursorY - 360) - currentPos2.m_y) * 180 / SHC_PI;
	float dirRad = shDeg2Rad(-dirDegree);

	CShVector3 pos(1.0f, 0.0f, 0.0f);


	CShVector3 onsenfout(cursorX - (currentPos2.m_x - 640), cursorY- (currentPos2.m_y - 360), 0.0f);

	float tg = pos.DotProduct(onsenfout);
	
	dirDegree = shRad2Deg(acosf(tg / onsenfout.GetLength()));

	SH_TRACE("degree: %f\n", dirDegree);
	SH_TRACE("rad: %f\n", dirRad);
	SH_TRACE("ntm: %f\n", acosf(tg));

	if (45 < dirDegree && 135 >= dirDegree)
	{
		m_look = e_look_left;
	}
	else if (135 < dirDegree && 225 >= dirDegree)
	{
		m_look = e_look_up;
	}
	else if (225 < dirDegree && 315 >= dirDegree)
	{
		m_look = e_look_right;
	}
	else
	{
		m_look = e_look_down;
	}

	//ShEntity2::SetRotation(m_aPoulpeAnimation[m_direction][m_currentId], 0, 0, dirRad);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
const CShVector2 CGamePoulpe::GetPosition() const
{
	return(ShEntity2::GetWorldPosition2(m_aPoulpeAnimation[m_direction][m_currentId]));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
const EPoulpeLook & CGamePoulpe::GetLook() const
{
	return(m_look);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::TakeDamage(int damage)
{
	m_life -= damage;

	if (0 >= m_life)
	{
		m_eState = e_state_dead;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::UpdateFromInputs(bool isLeft, bool isRight, bool isDown, bool isUp)
{
	//TODO : update box2d body and let sprite follow it

	if (m_tempoAnim >= 4)
	{
		m_tempoAnim = 0;

		CShVector2 currentPos = ShEntity2::GetWorldPosition2(m_aPoulpeAnimation[m_direction][m_currentId]);
		ShEntity2::SetShow(m_aPoulpeAnimation[m_direction][m_currentId], false);

		if (isLeft)
		{
			currentPos.m_x -= 5.0f;
			if (1 == m_direction) // was right
			{
				m_direction = 0;
				m_currentId = 0;
			}
			else
			{
				m_currentId = (m_currentId + 1) % m_aPoulpeAnimation[m_direction].GetCount();
			}
		}
		else if (isRight)
		{
			currentPos.m_x += 5.0f;
			if (0 == m_direction) // was left
			{
				m_direction = 1;
				m_currentId = 0;
			}
			else
			{
				m_currentId = (m_currentId + 1) % m_aPoulpeAnimation[m_direction].GetCount();
			}
		}
		else
		{
			m_currentId = 0;
		}

		ShEntity2::SetWorldPosition2(m_aPoulpeAnimation[m_direction][m_currentId], currentPos.m_x, currentPos.m_y);
		ShEntity2::SetShow(m_aPoulpeAnimation[m_direction][m_currentId], true);
	}

	m_tempoAnim++;
}

