#ifndef _PROCGEN_
#define _PROCGEN_

#include <stdlib.h>
#include <math.h>
#include <time.h>

class ProceduralGeneration
{
  private:
    const double pi;
    int taille;
    int pas2D;
    int nombre_octaves2D;
    int hauteur;
    int longueur;
    int longueur_max;
    double* valeurs2D;

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
};

#endif
