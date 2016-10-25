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
ProceduralGeneration::ProceduralGeneration(int l, int h, int p, int n) 
: m_taille(0)
, m_nombre_octaves2D(n)
, m_longueur(l)
, m_hauteur(h)
, m_pas2D(p)
{
	if (m_taille != 0)
	{
		SH_SAFE_FREE(m_valeurs2D);
	}

    m_longueur_max =  (int) ceil(m_longueur * pow(2, m_nombre_octaves2D  - 1)  / m_pas2D);
    int hauteur_max = (int) ceil(m_hauteur * pow(2, m_nombre_octaves2D  - 1)  / m_pas2D);

    m_valeurs2D = (double*) malloc(sizeof(double) * m_longueur_max * hauteur_max);

    srand(time(shNULL));

	int nVal = m_longueur_max * hauteur_max;
	for (int i = 0; i < nVal; ++i)
	{
		m_valeurs2D[i] = ((double)rand()) / RAND_MAX;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void ProceduralGeneration::destroyBruit2D() 
{
	if (m_longueur != 0)
	{
		free(m_valeurs2D);
	}

    m_longueur = 0;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::bruit2D(int i, int j) 
{
    return(m_valeurs2D[i * m_longueur_max + j]);
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
   int i = (int) (x / m_pas2D);
   int j = (int) (y / m_pas2D);

   double res = interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / m_pas2D, 1), fmod(y / m_pas2D, 1));

   return(res);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
double ProceduralGeneration::bruit_coherent2D(double x, double y, double persistance) 
{
    double somme = 0;
    double p = 1;
    int f = 1;

    for(int i = 0; i < m_nombre_octaves2D; ++i) 
	{
        somme += p * fonction_bruit2D(x * f, y * f);
        p *= persistance;
        f *= 2;
    }

    return(somme * (1 - persistance) / (1 - p));
}
