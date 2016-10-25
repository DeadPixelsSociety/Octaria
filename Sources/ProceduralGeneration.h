//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : ProceduralGeneration.h
// Author      : PRADAL & co
// Description : -
// PlatForm    : All
//--------------------------------------------------------------------------------------------------

#ifndef _PROCGEN_
#define _PROCGEN_

class ProceduralGeneration
{

public:

	/*
	l = Width | h = height | p = step | n = octave
	*/
	ProceduralGeneration(int l, int h, int p, int n);

	void destroyBruit2D();
	double bruit2D(int i, int j);
	double interpolation_cos1D(double a, double b, double x);
	double interpolation_cos2D(double a, double b, double c, double d, double x, double y);
	double fonction_bruit2D(double x, double y);
	double bruit_coherent2D(double x, double y, double persistance);


 private:

    int				m_taille;
    int				m_pas2D;
    int				m_nombre_octaves2D;
    int				m_hauteur;
    int				m_longueur;
    int				m_longueur_max;
    double*			m_valeurs2D;

 
};

#endif
