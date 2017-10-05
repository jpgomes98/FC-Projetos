/* Projeto 1- 5.10.2017*/
/* Ex 1.b */
/*João Pedro Gomes 87327
  Mariana Silva 87336*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  int n_max;
  float r, x; // r é o parametro geométrico, x é o valor inicial

  // inicializa o ficheiro output.dat onde vão ser escritos os valores de i e x
  ofstream output("output.dat");

  if (!(output.is_open()))
    {
      cout << "***** ERRO A ABRIR O FICHEIRO! Tente novamente! *****" << endl;
      return 1;
    }

  cout << " Introduza o parâmetro r: " << endl;
  while(!(cin >> r)) // Teste de validação de input
    {
      cin.clear();
      cin.ignore(100, '\n');
      cout<<"Introduza um número válido: ";
    }

  cout << " Introduza um x inicial: " << endl;
  while(!(cin >> x)) // Teste de validação de input
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
      cout<<"Introduza um número válido: \n";
    }
  
  /* ciclo das iteradas */
  
  for (int i = 0; i < n_max; i++)
    {
      x *= r;
      cout << "x(" << i << ")= " << x << endl;// imprime os valores no terminal
      output << i << " " << x << endl; // imprime os valores no ficheiro  
    }
  
  return 0;

}
