//---------- VecAnyD_main.cpp ----------
//GRUPO 2
//João Pedro Gomes e Mariana Silva
#include <iostream>
#include <cmath>
#include <fstream>
#include "VecAnyD.h"

int main()
{
    using namespace std;

    ofstream temp_x("Temp_x.dat");
    Vector barra(51);
    //como a barra tem 1 metro e hx=0.02 o vetor barra tem 51 elementos porque inicializa no 0.

    //Vetores auxiliares
    Vector medi(51);
    Vector barranew(barra);
    
    double ht= 0.01, hx=0.02, k=0.00122;
    
    barra.set(0, 473); //o primeiro elemento é fixo a 473K
    barra.set(50, 473);//tal como o último

    double ct;
    ct= (ht/(hx*hx))*k;
    
    for(unsigned i=1; i<50; i++)
      {
	barra.set(i, 373); //pontos intermédios inicializados a 373K.
      }

    for(unsigned t=0; t<30/ht; t++)
      {
	medi=med(barra);
	barranew=ct*(2*medi-2*barra)+barra;
	//equação de Fourier unidimensional atua no vetor inteiro
	//graças aos operadores definidos anteriormente.
       
	barra = barranew;
      }
    
    for(unsigned i=0; i<=50; i++)
      {
	//impreção no ficheiro dos valores da temperatura em cada ponto da barra ao fim dos 30s.
	temp_x << i*hx << " " << barra[i] << endl;
      }
    
    temp_x.close();
      
    return  0;
    
}
