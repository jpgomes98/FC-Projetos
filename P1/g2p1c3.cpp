/* Ex 1.c */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
  int n_max;
  double r, c, m;

  double x0, x1, x2;

  /* Parâmetros do PRNG */
  m = pow(2, 32);
  c = 1013904223;
  r = 1664525; 

  /* Incialização dos ficheiros */
  ofstream output("output2.dat");

  /*
  cout << " Introduza o parâmetro r: " << endl;
  cin >> r;
  */
  
  cout << " Introduza um x inicial: " << endl;
  cin >> x0;
  
  cout << " Introduza o número de iterações: " << endl;
  cin >> n_max;

  x1 = x0;
  
  /* ciclo das iteradas */
  
  for (int i = 0; i < n_max; i++)
    {

      x2 = fmod((r * x1 + c), m); // calcular x(i+1) com x(i) através da expressão do PRNG
      
      cout << " " << (x1 / m) << " " << (x2 / m) << endl; 
      output << (x1 / m) << " " << (x2 / m) << endl; // imprimir as variáveis normalizadas num ficheiro
      x1 = x2; 
      
    }
  return 0;

}
