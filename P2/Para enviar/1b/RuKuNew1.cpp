/*Projeto 2
 Grupo 2
1.b*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c2_header.h"

using namespace std;

using namespace forF;

double RuKuNew1 (double (*Fovm)(double t, double x, double v), double h, double t0, double x0, double v0)
{
  double k1_x, k2_x, k3_x, k4_x;
  double k1_v, k2_v, k3_v, k4_v;
  double t1;
      
  /* Cálculo dos declives do método Runge-Kutta */
      
  k1_x = v0;
  k1_v = (*Fovm)(t0, x0, v0);
      
  k2_x = v0 + (0.5) * h * k1_v;
  k2_v = (*Fovm)(t0 + 0.5 * h, x0 + (0.5) * h * k1_x, v0 + (0.5) * h * k1_v);
      
  k3_x = v0 + (0.5) * h * k2_v;
  k3_v = (*Fovm)(t0 + 0.5 * h, x0 + (0.5) * h * k2_x, v0 + (0.5) * h * k2_v);
      
  k4_x = v0 + h * k3_v;
  k4_v = (*Fovm)(t0 + h, x0 + h * k3_x, v0 + h * k3_v);


  forRK::x1 += (h/6.) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x);
  forRK::v1 += (h/6.) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v);
  t1 = t0 + h;
  
  return t1;
}
