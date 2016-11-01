//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : ProceduralGeneration.cpp
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#include "StdAfx.h"

#include "time.h"
//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ ProceduralGeneration::ProceduralGeneration(int width, int height, int step, int octave)
: m_octave(octave)
, m_width(width)
, m_height(height)
, m_step(step)
, m_maxWitdh(0)
, m_valeurs(shNULL)
, m_is1D(false)
{
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ProceduralGeneration::Initialize(bool is1D /*= false*/)
{
	if (shNULL != m_valeurs)
	{
		SH_SAFE_FREE(m_valeurs);
	}

	m_is1D = is1D;

	if (!is1D)
	{
		m_maxWitdh = (int)ceil(m_width * pow(2, m_octave - 1) / m_step);
		int height_max = (int)ceil(m_height * pow(2, m_octave - 1) / m_step);

		m_valeurs = (double*)malloc(sizeof(double) * m_maxWitdh * height_max);

		srand(time(shNULL));

		int nCount = m_maxWitdh * height_max;
		for (int i = 0; i < nCount; ++i)
		{
			m_valeurs[i] = ((double)rand()) / RAND_MAX;
		}
	}
	else
	{
		m_valeurs = (double*)malloc(sizeof(double) * (int)ceil(m_width * pow(2, m_octave - 1) / m_step));

		srand(time(NULL));
		int nCount = ceil(m_width * pow(2, m_octave - 1) / m_step);
		for (int i = 0; i < nCount; i++)
		{
			m_valeurs[i] = (double)rand() / RAND_MAX;
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ProceduralGeneration::Release()
{
	if (shNULL != m_valeurs)
	{
		SH_SAFE_FREE(m_valeurs);
	}

    m_width = 0;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
int ProceduralGeneration::Noise(int x, int y, int scale, int magnitude)
{
	double res = 0.0f;
	
	if (m_is1D)
	{
		res = fonction_bruit1D(x*scale);
	}
	else
	{ 
		res = fonction_bruit2D(x*scale, y*scale);
	}

	return((int)(res * magnitude));

	/*
	Note: Scale seems to broken all if != 1
	*/
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::bruit2D(int i, int j) 
{
    return(m_valeurs[i * m_maxWitdh + j]);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::interpolation_cos1D(double a, double b, double x) 
{
	double k = (1 - cos(x * SHC_PI)) / 2;

	return(a * (1 - k) + b * k);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::interpolation_cos2D(double a, double b, double c, double d, double x, double y) 
{
   double y1 = interpolation_cos1D(a, b, x);
   double y2 = interpolation_cos1D(c, d, x);

   return(interpolation_cos1D(y1, y2, y));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::fonction_bruit2D(double x, double y) 
{
   int i = (int) (x / m_step);
   int j = (int) (y / m_step);

   double res = interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / m_step, 1), fmod(y / m_step, 1));

   return(res);
}

//--------------------------------------------------------------------------------------------------
/// useless
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::bruit_coherent2D(double x, double y, double persistance) 
{
    double somme = 0;
    double p = 1;
    int f = 1;

    for (int i = 0; i < m_octave; ++i) 
	{
        somme += p * fonction_bruit2D(x * f, y * f);
        p *= persistance;
        f *= 2;
    }

    return(somme * (1 - persistance) / (1 - p));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::bruit1D(int i) 
{
	return m_valeurs[i];
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::fonction_bruit1D(double x)
{
	int i = (int)(x / m_step);
	return interpolation_cos1D(bruit1D(i), bruit1D(i + 1), fmod(x / m_step, 1));
}