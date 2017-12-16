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

#include "Matrix.h"
#include "timer.h"


  namespace param{  
    double **tt0;
    double **tt1;
    double k, dt, time, Tf, Tin, printIntv;
    double hxx, hyy, hx, hy, stop, Lx, Ly;
    int nx, ny, n_max;
  }

  template<class T>
  std::string ToString(T number){
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
  }

int main(){
  using namespace std;

  Timer t0;
  t0.start();

  cout<< "Enter parameters: Lx, Ly and n_max" << endl;
  cin >> param::Lx >> param::Ly >> param::n_max;
  cout<< "Enter parameters: hx, hy, ht and k" << endl;
  cin >> param::hx >> param::hy >> param::dt >> param::k;
  cout<< "Enter parameters: Tin and Tf" << endl;
  cin >> param::Tin >> param::Tf;
  cout<< "Enter parameters: save step in s" << endl;
  cin >> param::printIntv;
  cout<< "Enter parameters: stop criterium" << endl;
  cin >> param::stop;


  param::hxx = param::hx * param::hx;
  param::hyy = param::hy * param::hy;
  param::nx = param::Lx/param::hx + 1;
  param::ny = param::Ly/param::hy + 1;

  double maxht = 0.5 * (param::hxx * param::hyy)/((param::hxx + param::hyy) * param::k);
  cout << "Convergence criterium:  ht < " << maxht << endl;
  if( param::dt > maxht ){
    cout << "ht is too big!!!" << endl;
    exit(1);
  }
 

  cout << param::nx << "\t" << param::ny << "\t" << param::n_max << endl ;
  cout << param::hx << "\t" << param::hy << "\t" << param::dt << "\t" << param::k << endl ;


  cout << param::Tin << "\t" << param::Tf << endl ;


  Matrix tt0(param::nx, param::ny);
  tt0 = param::Tin;

  for(int j = 0; j < param::ny; j++){
    tt0(j,0) = param::Tf;
    tt0(j,param::nx-1) = param::Tf;
  }
  for(int i = 0; i < param::nx; i++){
    tt0(0,i) = param::Tf;
    tt0(param::ny-1,i) = param::Tf;
  }

  Matrix tt1(tt0);


  double Dif, printStep;
  printStep = param::printIntv;

  

  param::time = 0.;
  for(int iter = 1; iter <= param::n_max; iter++){

    tt1 = tt0 + (param::k * param::dt) * (vecDx2(tt0) / param::hxx + vecDy2(tt0) / param::hyy);

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
    
        for(int j = 0; j < param::ny; j++) 
        for(int i = 0; i < param::nx; i++) 
          output << ((double)i)*param::hx << "\t" << ((double)j)*param::hy << "\t" << tt1(j,i) << endl; 

      output.close();

      printStep += param::printIntv;   
    }
    tt0 = tt1;
      
  }
  t0.stop();
  cout << "################################################################" << endl; 
  cout << "Total time: " << t0.getElapsedTimeInMicroSec()  << " us\t" << t0.getElapsedTimeInSec() << " s"  << endl; 
  cout << "################################################################" << endl; 


  exit(0);
}

