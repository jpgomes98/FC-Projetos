#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Matrix.h"

using namespace std;


int main()
{

  double number;

  Matrix M(3,3);
  Matrix A(3,3);
  Matrix M_1(3,3);
  Matrix A_1(3,3);
  Matrix v(1,3);
  Matrix u(1,3);
  Matrix S(2,3);

  ifstream input("MatrizM.txt");
  ofstream output("Out.dat");

  srand(time (NULL));


  // A matriz M está definida no ficheiro MatrizM.dat
  for (int i = 1; i <= M.nlin(); i++)
    {
      for (int j = 1; j <= M.ncol(); j++)
    	{
    	  input >> number;
    	  M.set(i, j, number);
    	}
    }
 
  //A matriz A, a matriz S e o vetor ǘ são definidos aleatoriamente
  for (int i=1; i<= A.nlin(); i++)
    {
      for(int j=1; j<=A.ncol(); j++)
	     {
	       A.set(i, j, floor(((double) rand() / (double) RAND_MAX) * 10));
	     }
    }

   for (int i=1; i<= S.nlin(); i++)
    {
      for(int j=1; j<=S.ncol(); j++)
	     {
	       S.set(i, j, floor(((double) rand() / (double) RAND_MAX) * 10));
	     }
    }

  for(int i=1; i<= v.nlin(); i++)
    {
      int j=1;
      v.set(i, j, floor(((double) rand() / (double) RAND_MAX) * 10));
    }

  for(int i=1; i<= u.nlin(); i++)
    {
      int j=1;
      u.set(i, j, floor(((double) rand() / (double) RAND_MAX) * 10));
    }
 
 
 
  cout<< "Matrix M:"<<endl;
  cout<< M;
  output<< "Matrix M:"<<endl;
  output<< M << endl;
 
  cout<< "Matrix A:"<<endl;
  cout<< A;
  output<< "Matrix A:"<<endl;
  output<< A << endl;

  cout<< "Matrix S:"<<endl;
  cout<< S;
  output<< "Matrix S:"<<endl;
  output<< S << endl;

  cout<< "Vetor v:"<<endl;
  cout<< v;
  output<< "Vetor v:"<<endl;
  output<< v << endl;

  cout<< "Vetor u:"<<endl;
  cout<< u;
  output<< "Vetor u:"<<endl;
  output<< u << endl;

  cout<< "Matriz M*A"<<endl;
  cout<< M*A;
  output<< "Matrix M*A:"<<endl;
  output<< M*A <<endl;

  cout<< "Matrix M+A:"<<endl;
  cout<< M+A;
  output<< "Matrix M+A:"<<endl;
  output<< M+A <<endl;

  cout<< "Matrix M*S:"<<endl;
  cout<< M*S;
  output<< "Matrix M*S:"<<endl;
  output<< M*S <<endl;

  cout<< "Matrix M⁻¹:"<<endl;
  output<< "Matrix M⁻¹:"<<endl;

  M_1 = M.invert();
  
  cout<< M_1 << endl; 
  output<< M_1 << endl; 

  cout<< "Matrix M*M⁻¹:" << endl;
  cout<< M*M_1;
  output<< "Matrix M*M⁻¹:" << endl;
  output<< M*M_1  << endl;

  cout<< "Matrix A⁻¹:"<<endl;
  output<< "Matrix A⁻¹:"<<endl;

  A_1 = A.invert();

  cout<< A_1 << endl; 
  output<< A_1 << endl; 
  
  cout<< "Matrix A*A⁻¹:" << endl;
  cout<< A*A_1;
  output<< "Matrix A*A⁻¹:" << endl;
  output<< A*A_1  << endl;

  cout<< "M*v"<< endl;
  cout<< (M*v);
  output<< "M*v"<< endl;
  output<< (M*v) << endl;

  cout<< "Solução de Ax=v"<< endl;
  cout<< solve(A,v)<< endl;
  output<< "Solução de Ax=v"<< endl;
  output<< solve(A,v) << endl;

  cout<< "Produto interno <u,v>" << endl;
  cout<< dot(u,v)<< endl;
  output<< "Produto interno <u,v>" << endl;
  output<< dot(u,v)<< endl;

  cout<< "Produto externo uxv" << endl;
  cout<< cross(u,v)<< endl;
  output<< "Produto interno uxv" << endl;
  output<< cross(u,v);

//----------------------------------------------------------------------------------------------

  return 0;
}
