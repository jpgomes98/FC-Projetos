#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

namespace forRK {
  extern double x1[3];
  extern double v1[3];
}

namespace forF {
  extern double m;
  extern double k;
  extern double lbd;
  extern double F0;
  extern double wf;
}

double* D2_Oscilador_3D (double t, double x[3], double v[3]);

double* soma_vetorial(double coord[3], double k, double h, double c, double j);
double RuKuNew3 (double* (*Fovm)(double, double[3], double[3]), double h, double t0, double x0[3], double v0[3]);
