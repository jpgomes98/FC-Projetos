#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c4_header.h"

using namespace std;

using namespace forF;

using namespace forRK;

double ro (double x[3])
{
  double ro;
  ro = sqrt((x[0])*(x[0]) + (x[1])*(x[1]) + (x[2])*(x[2]));
  return ro;
}

double* soma_vetorial(double coord[3], double k, double h, double c, double j)
{
  static double soma[3];
  
  for (int i = 0; i < 3; i++)
    {
      if (i == j)
	{
	  soma[i] = coord[i] + c * h * k; 
	}
      else
	{
	  soma[i] = coord[i];
	}
    }
  
  return soma;  
}

double RuKuNew3 (double* (*Fovm)(double, double[3], double[3]), double h, double t0, double x0[3], double v0[3])
{
  double k1_x[3], k2_x[3], k3_x[3], k4_x[3];
  double k1_v[3], k2_v[3], k3_v[3], k4_v[3];
  double t1;
  double *p1, *p2, *p3, *p4;
      
  /* Cálculo dos declives do método Runge-Kutta */
  
   for (int i = 0; i < 3; i++)
    {
      
      k1_x[i] = v0[i];
      p1 = (*Fovm)(t0, soma_vetorial(x0, 0, h, 0, i), soma_vetorial(v0, 0, h, 0, i));
      k1_v[i] = p1[i];
      
      k2_x[i] = v0[i] + (0.5) * h * k1_v[i];
      p2 = (*Fovm)(t0 + 0.5 * h, soma_vetorial(x0, k1_x[i], h, 0.5, i), soma_vetorial(v0, k1_v[i], h, 0.5, i));
      k2_v[i] = p2[i];
      
      k3_x[i] = v0[i] + (0.5) * h * k2_v[i];
      p3 = (*Fovm)(t0 + 0.5 * h, soma_vetorial(x0, k2_x[i], h, 0.5, i),soma_vetorial(v0, k2_v[i], h, 0.5, i));
      k3_v[i] = p3[i];
      
      k4_x[i] = v0[i] + h * k3_v[i];
      p4 = (*Fovm)(t0 + h, soma_vetorial(x0, k3_x[i], h, 1, i), soma_vetorial(v0, k3_v[i], h, 1, i));
      k4_v[i] = p4[i];


      x1[i] += (h/6.) * (k1_x[i] + 2 * k2_x[i] + 2 * k3_x[i] + k4_x[i]);
      v1[i] += (h/6.) * (k1_v[i] + 2 * k2_v[i] + 2 * k3_v[i] + k4_v[i]);
      
    }
  
  t1 = t0 + h;
  
  return t1;
}
