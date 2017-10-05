/* Projeto 1- 5.10.2017*/
/* Ex 1.a */
/*João Pedro Gomes 87327
  Mariana Silva 87336*/

#include <iostream>

//dispensa a utilização de std::
using namespace std;

int main()
{
  //inicializam-se as variáveis
  int n_max=10;
  float r=.7, x=.5; // r é o parametro geométrico, x é o valor inicial
  

  // ciclo das iteradas 
  
  for (int i = 0; i < n_max; i++)
    {
      //x(n+1)=x(n)*r
      x *= r;
      cout << "x(" << i << ")= " << x << endl; //imprime para o terminal  
    }
  
  return 0;

}
