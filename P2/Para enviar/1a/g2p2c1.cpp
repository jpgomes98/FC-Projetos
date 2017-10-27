/*Projeto 2
 Grupo 2
1.a*/


#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

/* Funções utilizadas no Runge-Kutta relativas à Eq. do Movimento Harmónico */

double OH_Dx (double v)
{
  return v; 
}

double OH_Dv (double x, double v, double t, double w0, double b, double A, double wf)
{
  return -w0 * w0 * x -  b * v + A * sin(wf * t);
}


/* Método Runge-Kutta  */

void RungeKutta(double x0, double v0, double w0, double b, double h, double nmax, double A, double wf, int opt)
{
  double k1_x, k2_x, k3_x, k4_x;
  double k1_v, k2_v, k3_v, k4_v;
  double t = 0, tf = nmax * h;
  double x1 = 0, x2 = 0;
  double v1 = 0, v2 = 0;
  double n;

  v1 = v0;
  x1 = x0;
  
  
  ofstream output1("Kutta_1a_w0_3.dat");
  ofstream output2("Kutta_1a_w0.dat");
  ofstream output3("Kutta_1a_3w0.dat");
  
  while( t <= tf )
    {
      
      n = t / h;
      
      /* Cálculo dos declives do método Runge-Kutta */
      
      k1_x = v1;
      k1_v = OH_Dv(x1, v1, t, w0, b, A, wf);
      
      k2_x = v1 + (0.5) * h * k1_v;
      k2_v = OH_Dv(x1 + (0.5) * h * k1_x, v1 + (0.5) * h * k1_v, t + 0.5 * h, w0, b, A, wf);
      
      k3_x = v1 + (0.5) * h * k2_v;
      k3_v = OH_Dv(x1 + (0.5) * h * k2_x, v1 + (0.5) * h * k2_v, t + 0.5 * h, w0, b, A, wf);
      
      k4_x = v1 + h * k3_v;
      k4_v = OH_Dv(x1 + h * k3_x, v1 + h * k3_v, t + h, w0, b, A, wf);


      x2 = x1 + (h/6.) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x);
      v2 = v1 + (h/6.) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v);

      
      
      if (opt == 1)
	{
	  output1 << n << " " << t << " " << x1 << " " << v1 << endl;
	}
      else if (opt == 2)
	{
	  output2 << n << " " << t << " " << x1 << " " << v1 << endl;
	}
      else if (opt == 3)
	{
	  output3 << n << " " << t << " " << x1 << " " << v1 << endl;
	}
      
      x1 = x2;
      v1 = v2;
      t += h;
    }
}

int main ()
{
  double m = 1, k = 1, F0 = 0.5, wf, lbd = 0.5;
  double b, w0, A;

  double x0, v0;
  
  double nmax, h;
  int opt;

  ifstream input1("input_1a.txt");

  input1 >> x0;
  input1 >> v0;
  input1 >> nmax;
  input1 >> h;
  //input1 >> wf;

  w0 = sqrt(k / m);
  b = (lbd / m);
  A = F0 / m;

  cout << "*** G2P2C1 ***" << endl;
  cout << "Introduza o valor de wf pretendido (selecione o número correspondente): \n   (1) w0 / 3 \n   (2) w0 \n   (3) 3*w0 \n\n " << endl;
  cin >> opt;

  if (opt == 1)
    {
      wf = w0 / 3;
    }
  else if (opt == 2)
    {
      wf = w0;
    }
  else if (opt == 3)
    {
      wf = 3*w0;
    }
  else
    {
      return 1;
    }
  
  RungeKutta(x0, v0, w0, b, h, nmax, A, wf, opt);
  
  return 0;
}

