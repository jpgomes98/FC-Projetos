//---------- main.cpp ----------
//
//
#include <iostream> 
#include <fstream>  
#include <stdlib.h> 
#include <iomanip>
#include <math.h>   
#include <sstream>
#include <string>
#include <cstring>

#include "VecAnyD.h"


  namespace param{  
    double k, dt, time, Tf, Tin, printIntv;
    double hxx, hx, stop, Lx;
    int nx, n_max;
  }

  template<class T>
  std::string ToString(T number){
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
  }

int main(){
  using namespace std;


  cout<< "Enter parameters: Lx and n_max" << endl;
  cin >> param::Lx >> param::n_max;
  cout<< "Enter parameters: hx, ht and k" << endl;
  cin >> param::hx >> param::dt >> param::k;
  cout<< "Enter parameters: Tin and Tf" << endl;
  cin >> param::Tin >> param::Tf;
  cout<< "Enter parameters: save step in s" << endl;
  cin >> param::printIntv;
  cout<< "Enter parameters: stop criterium" << endl;
  cin >> param::stop;


  param::hxx = param::hx * param::hx;
  param::nx = param::Lx/param::hx + 1;


 double maxht = 0.5 * param::hxx/param::k;
  cout << "Convergence criterium:  ht < " << maxht << endl;
  if( param::dt > maxht ){
    cout << "ht is too big!!!" << endl;
   // exit(1);
  }
 

  cout << param::nx << "\t" << param::n_max << endl ;
  cout << param::hx << "\t" << param::dt << "\t" << param::k << endl ;
  cout << param::Tin << "\t" << param::Tf << endl ;


  Vector tt0(param::nx);
  Vector tt1(param::nx);

  tt0 = param::Tin;
  tt0[0] = param::Tf;
  tt0[param::nx-1] = param::Tf;

  tt1 = tt0;



  double Dif, printStep;
  printStep = param::printIntv;

  

  param::time = 0.;
  for(int iter = 1; iter <= param::n_max; iter++){

    tt1 = tt0 + (param::k * param::dt / param::hxx) * vecD2(tt0);

    Dif = SumAbsDif(tt1, tt0);

    param::time += param::dt;

    if( Dif < param::stop ) break;
    
    if( param::time >= printStep){
      cout << "Iter: " << iter << "\tTime: " << param::time << "\tDif: " <<  Dif << endl;

      string filename = "out_" + ToString<double>(param::time) + "s.txt";
      ofstream output(filename.c_str());
      if ( !output.is_open() ) {
        cerr << "Error opening file..." << endl;
        exit(1);
      }
    
      for(int i = 0; i < param::nx; i++) 
        output << ((double)i)*param::hx << "\t" << tt1[i] << endl; 

      output.close();

      printStep += param::printIntv;   
    }
    tt0 = tt1;
      
  }

  exit(0);
}

