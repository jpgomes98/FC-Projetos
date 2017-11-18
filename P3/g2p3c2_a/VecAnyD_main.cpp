//---------- VecAnyD_main.cpp ----------
//GRUPO 2
//
#include <iostream>
#include <cmath>
#include "VecAnyD.h"


int main()
{
  using namespace std;

  // aceita input usando os métodos da classe
  cout<<"Indique a dimensão dos vetores \n";
  unsigned n;
  cin>> n;
  cout<<"Elementos do primeiro vetor: \n";
  Vector r1(n); 


  for(unsigned i=0;i<n;i++){ 
    double vi; 
    cin>> vi; 
    r1.set(i,vi); // com o método set inicializamos ou alteramos os valores do vetor
  }
    
  cout<<"Elementos do segundo vetor: \n";
  Vector r2(n); 
  for(unsigned i=0;i<n;i++){ 
    double vi2; 
    cin>> vi2; 
    r2.set(i,vi2); // com o método set inicializamos ou alteramos os valores do vetor
  }

  cout<<"Indique o valor da constante: \n";
  double a; 
  cin>> a; 
    
  Vector r3(n);
  for(unsigned i=0; i<n; i++)
    {
      r3.set(i, 0);
    }
  
  r3=r1;
  cout << "r1: \t \t" << r1 << endl;
  cout << "r2: \t \t" << r2 << endl;
  cout << "r3=r1:  \t" << r3 << endl; 
  cout << "r1+r2= \t \t"<< r1+r2 << endl;
  cout << "r1+a= \t \t" << r1+a << endl;
  cout << "a+r1= \t \t" << a+r1 << endl;
  cout << "r1-r2= \t \t"<< r1-r2 << endl;
  cout << "-r1= \t \t" << -r1 << endl;
  cout << "r1*a= \t \t" << r1*a << endl;
  cout << "a*r2= \t \t" << a*r2 << endl;
    
  double prod;
  prod = dot(r1, r2);
  cout << "r1.r2= \t \t" << prod <<endl;

  double mod;
  mod = sqrt(dot(r1,r1));
  cout << "|r1|= \t \t" << mod <<endl;
    
  Vector medi(n);
  for(unsigned i=0; i<n; i++)
    {
      medi.set(i, 0);
    }
    
  medi=med(r1);
  cout << "med(r1)=\t" << medi << endl;
    
    
  return  0;
    
}
