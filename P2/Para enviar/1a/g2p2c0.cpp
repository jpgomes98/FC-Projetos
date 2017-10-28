/*Projeto 2
 Grupo 2
1.a*/

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


/* Funções utilizadas no método de Runge-Kutta relativas ao movimento harmónico */

double OH_Dx (double v)
{
  return v; 
}

double OH_Dv (double x, double v, double w0, double lbd)
{
  return -w0 * w0 * x - 2 * lbd * v;
}


void RungeKutta(double x0, double v0, double w0, double lbd, double h, double tf)
{
  double k1_x, k2_x, k3_x, k4_x;
  double k1_v, k2_v, k3_v, k4_v;
  double t = 0;
  double x1 = 0, x2 = 0;
  double v1 = 0, v2 = 0;

  v1 = v0;
  x1 = x0;
  
  
  ofstream outKutta("Oscilador_Kutta.dat");
  
  while( t <= tf)
    {

      /* Cálculo dos declives do método Runge-Kutta */
      
      k1_x = v1;
      k1_v = OH_Dv(x1, v1, w0, lbd);
      
      k2_x = v1 + (0.5) * h * k1_v;
      k2_v = OH_Dv(x1 + (0.5) * h * k1_x, v1 + (0.5) * h * k1_v, w0, lbd);
      
      k3_x = v1 + (0.5) * h * k2_v;
      k3_v = OH_Dv(x1 + (0.5) * h * k2_x, v1 + (0.5) * h * k2_v, w0, lbd);
      
      k4_x = v1 + h * k3_v;
      k4_v = OH_Dv(x1 + h * k3_x, v1 + h * k3_v, w0, lbd);


      x2 = x1 + (h/6.) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x);
      v2 = v1 + (h/6.) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v);

      outKutta << t << " " << x1 << " " << v1 << endl;
      
      x1 = x2;
      v1 = v2;
      t += h;
    }
}

int main()
{ 
  double k, m, b;
  double x0, v0;

  double w0, lbd;

  double h = 0.1;
  double tf;

  int opt;

  cout << "\x1b[1;32m" << "Indique que EDO pretende resolver (introduza os números identificadores)\n" << endl;

  cout << "\x1b[37m" << "   (1) Movimento Harmónico Simples \n   (2) Movimento Oscilatório Amortecido \n\n" << endl;
  cin >> opt;

  if (opt == 1)
    {
      cout << "\x1b[1;31m" << "Introduza k, m \x1b[37m" << endl;
      cin >> k;
      cin >> m;
    }
  else if (opt == 2)
    {
      cout << "\x1b[1;31m" << "Introduza k, m e b \x1b[37m" << endl;
      cin >> k;
      cin >> m;
      cin >> b;
    }
  else
    {
      cout << "Opção inválida" << endl;
      return 1;
    }
 
  cout << endl;
  
  cout << "\x1b[1;31m" << "Introduza as condições iniciais (x0 e v0 por esta ordem)\x1b[37m" << endl;
  cin >> x0;
  cin >> v0;

  cout << "\x1b[1;31m" << "Introduza o instante final da simulação \x1b[37m" << endl;
  cin >> tf;
  
  w0 = sqrt(k / m);

  if (opt == 1)
    {
      lbd = 0;
      RungeKutta(x0, v0, w0, lbd, h, tf);
    }

  else if (opt == 2)
    {
      lbd = b / (2. * m);
      RungeKutta(x0, v0, w0, lbd, h, tf);
    }
  
  return 0;
  
}
