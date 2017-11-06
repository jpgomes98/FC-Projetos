#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

namespace forRK {
  extern double x1;
  extern double v1;
}

namespace forF {
  extern double m;
  extern double k;
  extern double lbd;
  extern double F0;
  extern double wf;
}

double D2_Oscilador (double t, double x, double v);
double RuKuNew1 (double (*Fovm)(double t, double x, double v), double h, double t0, double x0, double v0);
