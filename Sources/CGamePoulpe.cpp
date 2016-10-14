//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CGamePoulpe.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ CGamePoulpe::CGamePoulpe(void)
: m_eState(e_state_init)
, m_direction(0)
, m_currentId(0)
, m_tempoAnim(0)
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
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::Initialize(CShIdentifier levelIdentifier)
{
	char spriteName[256];
	char spriteIdent[256];

	/* walk without weapon */
	for (int i = 0; i < 5; i++)
	{
		sprintf(spriteName, "sprite_octaria_poulpe_left_%d", i);
		sprintf(spriteIdent, "poulpe_left_%d", i);
		ShEntity2 * pEntity = ShEntity2::Create(levelIdentifier, CShIdentifier(spriteName), CShIdentifier("layer_default"), CShIdentifier("octaria"), CShIdentifier(spriteIdent), CShVector3(0.0f, 0.0f, 4.0f), CShEulerAngles(), CShVector3(1.0f, 1.0f, 1.0f), false);
		SH_ASSERT(shNULL != pEntity);
		m_aPoulpeAnimation[0].Add(pEntity);
	}
	ShEntity2::SetShow(m_aPoulpeAnimation[0][0], true);

	for (int i = 0; i < 5; i++)
	{
		sprintf(spriteName, "sprite_octaria_poulpe_right_%d", i);
		sprintf(spriteIdent, "poulpe_right_%d", i);
		ShEntity2 * pEntity = ShEntity2::Create(levelIdentifier, CShIdentifier(spriteName), CShIdentifier("layer_default"), CShIdentifier("octaria"), CShIdentifier(spriteIdent), CShVector3(0.0f, 0.0f, 4.0f), CShEulerAngles(), CShVector3(1.0f, 1.0f, 1.0f), false);
		SH_ASSERT(shNULL != pEntity);
		m_aPoulpeAnimation[1].Add(pEntity);
	}

	m_eState = e_state_init;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void CGamePoulpe::Update(bool isLeft, bool isRight)
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
			UpdateFromInputs(isLeft, isRight);
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
void CGamePoulpe::UpdateFromInputs(bool isLeft, bool isRight)
{
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

