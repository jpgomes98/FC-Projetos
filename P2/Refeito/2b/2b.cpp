#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

#define GNUPLOT "gnuplot gnuplot_config_2b.plt"

namespace forRK {
  double x1[3];
  double v1[3];
  double r;
  double v;
}

namespace forF {
  double m;
  double k;
  double lbd;
  double F0;
  double wf;
}
  

namespace Grav {
  double ms;
  double G;
  double Rt;
  double Mt;
  double A;
  double p0;
  double a_barra;
}

using namespace std;

using namespace Grav;

using namespace forF;

using namespace forRK;

double dist (double vetor[3])
{
  return sqrt(vetor[0]*vetor[0] + vetor[1]*vetor[1] + vetor[2]*vetor[2]);
}

double* D2_Oscilador_3d (double t, double xm[3], double vm[3])
{
  static double a[3];
  a[0] = -(k / m) * xm[0] - (lbd / m) * vm[0] + (F0 / m) * sin(wf * t);
  a[1] = 0;
  a[2] = 0;
    
  return a;
}

double* D2_Satelite_3d (double t, double xs[3], double vs[3])
{
  static double a[3];
  double Fg_m, Fa_m;

  r = sqrt(xs[0]*xs[0] + xs[1]*xs[1] + xs[2]*xs[2]);
  v = sqrt(vs[0]*vs[0] + vs[1]*vs[1] + vs[2]*vs[2]);

  /* Calcular o módulo da aceleração em r e v */
  
  Fg_m = -G * (Mt/(r*r*r));
  Fa_m = (-1. / ms) * (0.5) * p0 * exp(-(r - Rt)/a_barra) * (A) * v;

  if ((r - Rt) <= 0)
    {
      cout << "O satélite já aterrou na Terra!" << endl;
      system(GNUPLOT);
      return 0;
    }

  /* Obter a aceleração em cada componente */

  for (int i = 0; i < 3; i++)
    {
      a[i] = Fg_m * xs[i] + Fa_m * vs[i];
    }
  
  return a;
}

double RuKuNew3 (double* (*Fovm3)(double, double[3], double[3]), double h, double t0, double x0[3], double v0[3])
{ 
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
      x1[i] = x0[i] + (h/6.) * (k1_x[i] + 2 * k2_x[i] + 2 * k3_x[i] + k4_x[i]);
      v1[i] = v0[i] + (h/6.) * (k1_v[i] + 2 * k2_v[i] + 2 * k3_v[i] + k4_v[i]);
    }

  t1 = t0 + h;
  
  return t1;
}


int main ()
{
  double t0 = 0;
  double t;
  double h;
  int nmax;
  int n_step;
  
  ifstream input("parametros_sistema.txt");
  ofstream output("dados_2b.txt");

  /* Definir os valores guardados no namespace forF */

  G = 6.674e-11;
  ms = 1e4;
  Mt = 5.972e24;
  Rt = 6.371e6;
  A = 10;
  p0 = 1.225;
  a_barra = 8000;

  /* Inicializar o sistema */

  /*input >> x0[0] >> x0[1] >> x0[2];
  input >> v0[0] >> v0[1] >> v0[2];*/

  x1[0] = Rt + 80e3;
  x1[1] = 0;
  x1[2] = 0;
  v1[0] = 0;
  v1[1] = 11.05e3;
  v1[2] = 0;

  
  input >> nmax;
  input >> n_step;
  input >> h;

  
  /* Resolver EDO */

  //Fovm = &D2_Oscilador;
  
  for (int i = 0; i < nmax; i++)
    {
      t = RuKuNew3(&D2_Satelite_3d, h, t, x1, v1);
      if (i % n_step == 0)
	{	  
	  output << i << " " << t << " " << x1[0] << " " <<  x1[1] << " " <<  x1[2] << " " << (r - Rt) << " " << v1[0] << " " << v1[1] << " " << v1[2] << " " << v << " " << endl;
	}
    }

  system(GNUPLOT);

  
  return 0;
}

