/* Projeto 1- 5.10.2017*/
/* Ex 1.c */
/*João Pedro Gomes 87327
  Mariana Silva 87336*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
  //inicializar os parâmetros
  int n_max;
  double r, c, m;
  double x0, x1, x2;

  /* Parâmetros do PRNG */
  m = pow(2, 32);
  c = 1013904223;
  r = 1664525; 

  /* Inicialização dos ficheiros */
  ofstream output("output2.dat");

  if (!(output.is_open()))
    {
      cout << "***** ERRO A ABRIR O FICHEIRO! Tente novamente! *****" << endl;
      return 1;
    }

  /*** Pedir input ao utilizador ***/
  
  cout << " Introduza um x inicial: " << endl;
  while(!(cin >> x0)) // Teste de validação de input
    {
      cin.clear();
      cin.ignore(100, '\n');
      cout<<"Introduza um número válido: ";
    }
  
  cout << " Introduza o número de iterações: " << endl;
  while(!(cin >> n_max)) // Teste de validação de input
    {
      cin.clear();
      cin.ignore(100, '\n');
      cout<<"Introduza um número válido: ";
    }

  /*********************************/
  
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
