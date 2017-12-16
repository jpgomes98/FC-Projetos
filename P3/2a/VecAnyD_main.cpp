//---------- VecAnyD_main.cpp ----------
//
//
#include <iostream>
#include "VecAnyD.h"


int main()
{
    using namespace std;


    // aceita input usando os métodos da classe
     cout<<"de a dimensao dos vetores \n";
    unsigned n;
     cin>> n;
     cout<<"de todos os elementos do 1o vetor \n";
    Vector r1(n); 


    for(unsigned i=0;i<n;i++){ 
      double vi; 
       cin>> vi; 
      r1.set(i,vi); // com o método set inicializamos ou alteramos os valores do vetor
    }
    cout << "r1: " << r1 << endl;
    cout << "|r1|^2: " << dot(r1,r1) << endl;
    cout << "|r1|: " << modulo(r1) << endl;
    cout << "med(r1): " << med(r1) << endl;

    Vector r2(n); 
    r2 = r1 * 2.;
    cout << "r1 * 2: " << r2 << endl;
    r2 = 2. * r1;
    cout << "2 * r1: " << r2 << endl;
    r2 = -r1;
    cout << "-r1: " << r2 << endl;

   

      
    return  0;
    
}
