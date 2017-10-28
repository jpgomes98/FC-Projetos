#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c4_header.h"

namespace forRK {
   double x1[3];
   double v1[3];
}

namespace forF {
   double m;
   double k;
   double lbd;
   double F0;
   double wf;

  // alínea 2.b

  double G;
  double m_terra;
  double ro0;
  double R_terra;
  double A_satelite;
  double m_satelite;
  double a_barra;
  
}


using namespace std;

using namespace forF;

using namespace forRK;

int main ()
{
  double x0[3], v0[3];
  double t0 = 0;
  double t;
  double h;
  int nmax, n_jump;

  double* (*Fovm3)(double, double[3] , double[3]); /* Ponteiro para função que retorna ponteiros */

  //double **sistema;

  ifstream input5("parametros_sistema.txt");
  ofstream output6("satelites.dat");

  /* Definir os valores guardados no namespace forF */

  m = 1;
  k = 1;
  lbd = 0.5;
  F0 = 0.5;
  wf = 1;

  
  G = 6.67e-11;
  m_terra = 5.972e24;
  ro0= 1.225;
  R_terra= 6.371e6;
  A_satelite= 10;
  m_satelite =1e4;
  x0[0]=0;
  a_barra=8000;


  x0[0]= R_terra+80000;
  x0[1]= 0;
  x0[2]= 0;

  v0[0]=0;
  v0[1]=11.2;
  v0[2]=0;

  
  input5 >> n_jump;
  input5 >> nmax;
  input5 >> h;

  /*sistema = new double*[nmax];
  for (int i = 0; i < nmax; i++)
  sistema[i] = new double[3];*/

  /* Resolver EDO */

  x1[0] = x0[0];
  v1[0] = v0[0];
  x1[1] = x0[1];
  v1[1] = v0[1];
  x1[2] = x0[2];
  v1[2] = v0[2];


  t = t0;

  Fovm3 = &D2_Satelite;
  
  for (int i = 0; i < nmax; i++)
    {
      t = RuKuNew3(Fovm3, h, t, x1, v1);
      /*sistema[i][0] = t;
      sistema[i][1] = forRK::x1;
      sistema[i][2] = forRK::v1;*/
      output6 << t << " " << x1[0] << endl;
    }

  /*for (int i = 0; i < nmax; i++)
    {
      delete[] sistema[i];
    }
  
  delete[] sistema;
  */
  return 0;
}
