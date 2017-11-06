#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

#define GNUPLOT "gnuplot gnuplot_config_2a.plt"

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
}

using namespace std;

using namespace forF;

double* D2_Oscilador_3d (double t, double x[3], double v[3])
{
  static double a[3];
  a[0] = -(k / m) * x[0] - (lbd / m) * v[0] + (F0 / m) * sin(wf * t);
  a[1] = 0;
  a[2] = 0;
    
  return a;
}

double RuKuNew3 (double* (*Fovm3)(double, double[3], double[3]), double h, double t0, double x0[3], double v0[3])
{

  using namespace forRK; // utilizar localmente
  
  double k1_x[3], k2_x[3], k3_x[3], k4_x[3];
  double k1_v[3], k2_v[3], k3_v[3], k4_v[3];
  double t1;

  /* Variáveis auxiliares*/

  double *p;
  double xax[3], vax[3]; // calcular as posições intermédias onde os declives e Fovm3 são calculados
      
  /* Cálculo dos declives do método Runge-Kutta */

  // Cálcular cada um dos declives separadamente porque Fovm (que recebe 2 arrays e 1 double) retorna um ponteiro 


  /* K1 */
  p = Fovm3(t0, x0, v0);
  for (int i = 0; i < 3; i++)
    {
      k1_x[i] = v0[i];
      k1_v[i] = p[i];
      xax[i] = x0[i] + (0.5) * h * k1_x[i];
      vax[i] = v0[i] + (0.5) * h * k1_v[i];
    }

  /* K2 */

  p = Fovm3(t0 + 0.5 * h, xax, vax);
  for (int i = 0; i < 3; i++)
    {
      k2_x[i] = vax[i];
      k2_v[i] = p[i];
      xax[i] = x0[i] + (0.5) * h * k2_x[i];
      vax[i] = v0[i] + (0.5) * h * k2_v[i];
    }

  /* K3 */

  p = Fovm3(t0 + 0.5 * h, xax, vax);
  for (int i = 0; i < 3; i++)
    {
      k3_x[i] = vax[i];
      k3_v[i] = p[i];
      xax[i] = x0[i] + h * k3_x[i];
      vax[i] = v0[i] + h * k3_v[i];
    }

  /* K4 */

  p = Fovm3(t0 + h, xax, vax);
  for (int i = 0; i < 3; i++)
    {
      k4_x[i] = vax[i];
      k4_v[i] = p[i];
      xax[i] = x0[i] + (0.5) * h * k3_x[i];
      vax[i] = v0[i] + (0.5) * h * k3_v[i];
    }
  
  /*
  k1_x = v0;
  k1_v = Fovm(t0, x0, v0);
      
  k2_x = v0 + (0.5) * h * k1_v;
  k2_v = Fovm(t0 + 0.5 * h, x0 + (0.5) * h * k1_x, v0 + (0.5) * h * k1_v);
      
  k3_x = v0 + (0.5) * h * k2_v;
  k3_v = Fovm(t0 + 0.5 * h, x0 + (0.5) * h * k2_x, v0 + (0.5) * h * k2_v);
      
  k4_x = v0 + h * k3_v;
  k4_v = Fovm(t0 + h, x0 + h * k3_x, v0 + h * k3_v);
  */

  for (int i = 0; i < 3; i++)
    {
      forRK::x1[i] += (h/6.) * (k1_x[i] + 2 * k2_x[i] + 2 * k3_x[i] + k4_x[i]);
      forRK::v1[i] += (h/6.) * (k1_v[i] + 2 * k2_v[i] + 2 * k3_v[i] + k4_v[i]);
    }

  t1 = t0 + h;
  
  return t1;
}


int main ()
{

  using namespace forRK;
  
  double x0[3], v0[3], t0 = 0;
  double t;
  double h;
  int nmax;

  /* double* (*Fovm)(double x0, double v0, double t0);  Ponteiro para função */

  
  ifstream input("parametros_sistema.txt");
  ofstream output("dados_2a.txt");

  /* Definir os valores guardados no namespace forF */

  m = 1;
  k = 1;
  lbd = 0.5;
  F0 = 0.5;
  wf = 3;


  input >> x0[0] >> x0[1] >> x0[2];
  input >> v0[0] >> v0[1] >> v0[2];
  input >> nmax;
  input >> h;

  
  /* Resolver EDO */

  for (int i = 0; i < 3; i++)
    {
      x1[i] = x0[i];
      v1[i] = v0[i];
    }
  t = t0;

  //Fovm = &D2_Oscilador;
  
  for (int i = 0; i < nmax; i++)
    {
      t = RuKuNew3(&D2_Oscilador_3d, h, t, x1, v1);
      output << t << " " << x1[0] << " " <<  x1[1] << " " <<  x1[2] << " " << v1[0] << " " << v1[1] << " "<< v1[2] << " " << endl;
    }

  system(GNUPLOT);

  
  return 0;
}

