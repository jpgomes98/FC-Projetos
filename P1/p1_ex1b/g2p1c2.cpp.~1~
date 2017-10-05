/* Ex 1.b */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  int n_max;
  float r, x; // r é o parametro geométrico, x é o valor inicial

  ofstream output("output.dat");

  /* ciclo das iteradas */

  cout << " Introduza o parâmetro r: " << endl;
  cin >> r;

  cout << " Introduza um x inicial: " << endl;
  cin >> x;

  cout << " Introduza o número de iterações: " << endl;
  cin >> n_max;
  
  for (int i = 0; i < n_max; i++)
    {

      x *= r;
      cout << "x(" << i << ")= " << x << endl;
      output << i << " " << x << endl;
      
    }
  return 0;

}
