#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c3_header.h"

using namespace std;

using namespace forF;

using namespace forRK;

double* D2_Oscilador_3D (double t, double x[3], double v[3])
{
  double a[3];

  a[0] = -(k / m) * x[0] - (lbd / m) * v[0] + (F0 / m) * sin(wf * t);
  a[1] = 0;
  a[2] = 0;
  
  return a;
}


