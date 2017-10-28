#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c4_header.h"

using namespace std;

using namespace forF;

using namespace forRK;

double* D2_Oscilador_3D (double t, double x[3], double v[3])
{
  static double a[3];

  a[0] = -(k / m) * x[0] - (lbd / m) * v[0] + (F0 / m) * sin(wf * t);
  a[1] = 0;
  a[2] = 0;
  
  return a;
}

double* D2_Satelite (double t, double x[3], double v[3])
{
  static double b[3];

  b[0] = -G * ((m_terra)/(pow(ro(x), 3))) * x[0] - 0.5 * ro0 * exp(-((x[2] - R_terra))/a_barra)* (A_satelite / m_satelite) * ro(v) * v[0];
  b[1] = -G * ((m_terra)/(pow(ro(x), 3))) * x[1] - 0.5 * ro0 * exp(-((x[2] - R_terra))/a_barra)*  (A_satelite / m_satelite) * ro(v) * v[1];
  b[2] = -G * ((m_terra)/(pow(ro(x), 3))) * x[2] - 0.5 * ro0 * exp(-((x[2] - R_terra))/a_barra) * (A_satelite / m_satelite) * ro(v) * v[2];
  
  return b;
}


