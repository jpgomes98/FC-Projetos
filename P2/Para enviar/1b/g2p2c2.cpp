/*Projeto 2
 Grupo 2
1.b*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c2_header.h"

namespace forRK {
   double x1;
   double v1;
}

namespace forF {
   double m;
   double k;
   double lbd;
   double F0;
   double wf;
}

using namespace std;

using namespace forF;

int main ()
{
  double x0, v0, t0 = 0;
  double t;
  double h;
  int nmax;

  double (*Fovm)(double x0, double v0, double t0); /* Ponteiro para função */

  double **sistema;

  ifstream input5("parametros_sistema.txt");
  ofstream output5("RK_generico_1b.txt");

  /* Definir os valores guardados no namespace forF */

  m = 1;
  k = 1;
  lbd = 0.5;
  F0 = 0.5;
  wf = 3;

  /*Importar do ficheiro os valores dos parâmetros iniciais*/
  input5 >> x0;
  input5 >> v0;
  input5 >> nmax;
  input5 >> h;

  /*Matriz de memória dinâmica*/
  sistema = new double*[nmax];
  for (int i = 0; i < nmax; i++)
    sistema[i] = new double[3];

  /* Resolver EDO */

  forRK::x1 = x0;
  forRK::v1 = v0;
  t = t0;

  Fovm = &D2_Oscilador;
  
  for (int i = 0; i < nmax; i++)
    {
      t = RuKuNew1(Fovm, h, t, forRK::x1, forRK::v1);
      sistema[i][0] = t;
      sistema[i][1] = forRK::x1;
      sistema[i][2] = forRK::v1;
    }

  for (int i = 0; i < nmax; i++)
    {
      output5 << sistema[i][0] << " " << sistema[i][1] << " " << sistema[i][2] << endl;
    }

  /*Limpeza da matriz */
  for (int i = 0; i < nmax; i++)
    {
      delete[] sistema[i];
    }
  
  delete[] sistema;
  
  return 0;
}

