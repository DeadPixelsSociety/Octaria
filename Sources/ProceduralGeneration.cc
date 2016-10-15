#include "ProceduralGeneration.h"
#include <math.h>       /* sqrt */

ProceduralGeneration::ProceduralGeneration(int l, int h, int p, int n) : pi(3.14159265), taille(0)
{
    nombre_octaves2D = n;
    if(taille != 0)
        free(valeurs2D);
    longueur = l;
    hauteur = h;
    pas2D = p;
    longueur_max = (int) ceil(longueur * pow(2, nombre_octaves2D  - 1)  / pas2D);
    int hauteur_max = (int) ceil(hauteur * pow(2, nombre_octaves2D  - 1)  / pas2D);

    valeurs2D = (double*) malloc(sizeof(double) * longueur_max * hauteur_max);

    srand(time(NULL));
    int i;
    for(i = 0; i < longueur_max * hauteur_max; i++)
        valeurs2D[i] = ((double) rand()) / RAND_MAX;
}

void ProceduralGeneration::destroyBruit2D() {
    if(longueur != 0)
        free(valeurs2D);
    longueur = 0;
}

double ProceduralGeneration::bruit2D(int i, int j) {
    return valeurs2D[i * longueur_max + j];
}

double ProceduralGeneration::interpolation_cos1D(double a, double b, double x) {
   double k = (1 - cos(x * pi)) / 2;
    return a * (1 - k) + b * k;
}

double ProceduralGeneration::interpolation_cos2D(double a, double b, double c, double d, double x, double y) {
   double y1 = interpolation_cos1D(a, b, x);
   double y2 = interpolation_cos1D(c, d, x);
   return  interpolation_cos1D(y1, y2, y);
}

double ProceduralGeneration::fonction_bruit2D(double x, double y) {
   int i = (int) (x / pas2D);
   int j = (int) (y / pas2D);
   return interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / pas2D, 1), fmod(y / pas2D, 1));
}

double ProceduralGeneration::bruit_coherent2D(double x, double y, double persistance) {
    double somme = 0;
    double p = 1;
    int f = 1;
    int i;

    for(i = 0 ; i < nombre_octaves2D ; i++) {
        somme += p * fonction_bruit2D(x * f, y * f);
        p *= persistance;
        f *= 2;
    }
    return somme * (1 - persistance) / (1 - p);
}
