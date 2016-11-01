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

	explicit		ProceduralGeneration	(int width, int height, int step, int octave);

	void			Initialize				(bool is1D = false);
	void			Release					(void);

	int				Noise					(int x, int y, int scale, int magnitude);

private: 

	double			fonction_bruit2D		(double x, double y);
	double			fonction_bruit1D		(double x);

	double			bruit2D					(int i, int j);
	double			interpolation_cos2D		(double a, double b, double c, double d, double x, double y);


	double			bruit1D					(int i);
	double			interpolation_cos1D		(double a, double b, double x);


	double			bruit_coherent2D		(double x, double y, double persistance);

private:

    int				m_step;
	int				m_octave;
    int				m_height;
    int				m_width;
    int				m_maxWitdh;
    double *		m_valeurs;
	bool			m_is1D;

};

#endif
