#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Matrix.h"

using namespace std;


int main()
{
  clock_t t;
  clock_t t2;
  clock_t t3;

  double number1;
  double number2;
  double number3;


  Matrix M9(9,9);
  Matrix M_inv9(9,9);

  Matrix M99(99,99);
  Matrix M_inv99(99,99);

  Matrix M999(999,999);
  Matrix M_inv999(999,999);

  ifstream input1("matrix_9.txt");
  ifstream input2("matrix_99.txt");
  ifstream input3("matrix_999.txt");

  ofstream output1("inversa_9.dat");
  ofstream output2("inversa_99.dat");
  ofstream output3("inversa_999.dat");

  for(int i=1; i<=M9.ncol(); i++)
  {
  	for(int j=1; j<=M9.nlin(); j++)
  	{
    	  input1 >> number1;
    	  M9.set(i, j, number1);
  	}
  }

  for(int i=1; i<=M99.ncol(); i++)
  {
  	for(int j=1; j<=M99.nlin(); j++)
  	{
    	  input2 >> number2;
    	  M99.set(i, j, number2);
  	}
  }

  for(int i=1; i<=M999.ncol(); i++)
  {
  	for(int j=1; j<=M999.nlin(); j++)
  	{
    	  input3 >> number3;
    	  M999.set(i, j, number3);
  	}
  }

  t = clock();

  cout << "A calcular a inversa para N_Max=9 ..." <<endl;

  M_inv9= M9.invert();

  t = clock() - t;

  cout<< "Demorou "<< t<< " clicks a inverter a matriz 9x9, ou seja, "<< ((float)t)/CLOCKS_PER_SEC << " segundos." << endl;

  output1<< M_inv9;

  //---------------------------------------------------------------------------------------//

  t2 = clock();

  cout << "A calcular a inversa para N_Max=99 ..." <<endl;

  M_inv99= M99.invert();

  t2 = clock() - t2;

  cout<< "Demorou "<< t2<< " clicks a inverter a matriz 99x99, ou seja, "<< ((float)t2)/CLOCKS_PER_SEC << " segundos." << endl;

  output2<< M_inv99;

  //--------------------------------------------------------------------------------------//

  t3 = clock();

  cout << "A calcular a inversa para N_Max=999 ..." <<endl;

  M_inv999= M999.invert();

  t3 = clock() - t3;

  cout<< "Demorou "<< t3<< " clicks a inverter a matriz 999x999, ou seja, "<< ((float)t3)/CLOCKS_PER_SEC << " segundos." << endl;
  
  output3<< M_inv999;

  return 0;
}
