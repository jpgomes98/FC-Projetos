#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c3_header.h"

using namespace std;

using namespace forF;

using namespace forRK;

double soma_vetorial

double RuKuNew3 (double* (*Fovm)(double, double[3], double[3]), double h, double t0, double* x0, double v0[3])
{
  double k1_x[3], k2_x[3], k3_x[3], k4_x[3];
  double k1_v[3], k2_v[3], k3_v[3], k4_v[3];
  double t1;
  double *p1, *p2, *p3, *p4;
      
  /* Cálculo dos declives do método Runge-Kutta */
  
   for (int i = 0; i < 3; i++)
    {
      
      k1_x[i] = v0[i];
      p1 = (*Fovm)(t0, x0[i], v0[i]);
      k1_v[i] = p1[i];
      
      k2_x[i] = v0[i] + (0.5) * h * k1_v[i];
      p2 = (*Fovm)(t0 + 0.5 * h, x0[i] + (0.5) * h * k1_x[i], v0[i] + (0.5) * h * k1_v[i]);
      k2_v[i] = p2[i];
      
      k3_x[i] = v0[i] + (0.5) * h * k2_v[i];
      p3 = (*Fovm)(t0 + 0.5 * h, x0[i] + (0.5) * h * k2_x[i], v0[i] + (0.5) * h * k2_v[i]);
      k3_v[i] = p3[i];
      
      k4_x[i] = v0[i] + h * k3_v[i];
      p4 = (*Fovm)(t0 + h, x0[i] + h * k3_x[i], v0[i] + h * k3_v[i]);
      k4_v[i] = p4[i];


      x1[i] += (h/6.) * (k1_x[i] + 2 * k2_x[i] + 2 * k3_x[i] + k4_x[i]);
      v1[i] += (h/6.) * (k1_v[i] + 2 * k2_v[i] + 2 * k3_v[i] + k4_v[i]);
      
    }
  
  t1 = t0 + h;
  
  return t1;
}
