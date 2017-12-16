

#include <iostream> 
#include <fstream>  
#include <stdlib.h> 
#include <iomanip>
#include <math.h>   
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>


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





    param::tt0 = new double*[param::ny];
    param::tt1 = new double*[param::ny];
    for(int j = 0; j < param::ny; j++) {
      param::tt0[j] = new double[param::nx];
      param::tt1[j] = new double[param::nx];
    }

    
    for(int j = 0; j < param::ny; j++) 
    for(int i = 0; i < param::nx; i++) {
      param::tt0[j][i] = param::Tin;
      param::tt1[j][i] = param::Tin;
    }

    for(int j = 0; j < param::ny; j++){
      param::tt0[j][0] = param::Tf;
      param::tt1[j][0] = param::Tf;
      param::tt0[j][param::nx-1] = param::Tf;
      param::tt1[j][param::nx-1] = param::Tf;
    }
    for(int i = 0; i < param::nx; i++){
      param::tt0[0][i] = param::Tf;
      param::tt1[0][i] = param::Tf;
      param::tt0[param::ny-1][i] = param::Tf;
      param::tt1[param::ny-1][i] = param::Tf;
    }

    double Dif, printStep;
    printStep = param::printIntv;

    
    param::time = 0.;
    double **tmp;
    
    for(int iter = 1; iter <= param::n_max; iter++){
      Dif = 0.;
      for(int j = 1; j < param::ny-1; j++) 
	for(int i = 1; i < param::nx-1; i++) {
	  double txx = param::tt0[j][i+1] - 2.*param::tt0[j][i] + param::tt0[j][i-1];
	  double tyy = param::tt0[j+1][i] - 2.*param::tt0[j][i] + param::tt0[j-1][i];
	  param::tt1[j][i] = param::tt0[j][i] + param::k * param::dt * (txx/param::hxx + tyy/param::hyy);

	  Dif += abs(param::tt1[j][i] - param::tt0[j][i]);
	}
      param::time += param::dt;
      if( Dif < param::stop ) break;
      cout << "Iter: " << iter << "\tTime: " << param::time << "\tDif: " <<  Dif << endl;
      
      if( param::time >= printStep){
        cout << "Iter: " << iter << "\tTime: " << param::time << "\tDif: " <<  Dif << endl;

        string filename = "out_" + ToString<double>(param::time) + "s.txt";
        ofstream output(filename.c_str());
        if ( !output.is_open() ) {
          cerr << "Error opening file..." << endl;
          exit(1);
        }
	cout<< "Using output file data " << filename << endl;

      
        for(int j = 0; j < param::ny; j++) 
	  for(int i = 0; i < param::nx; i++) 
	    output << ((double)i)*param::hx << "\t" << ((double)j)*param::hy << "\t" << param::tt1[j][i] << endl; 

        output.close();

        printStep += param::printIntv;   
      }
    
      /*for(int j = 1; j < param::ny-1; j++) 
      for(int i = 1; i < param::nx-1; i++) 
        tt0[j][i] = tt1[j][i];*/

      tmp = param::tt0;
      param::tt0 = param::tt1;
      param::tt1 = tmp;
      
  }

  for(int j = 0; j < param::ny; j++) {
    delete[] param::tt0[j];
    delete[] param::tt1[j];
  }
  delete[] param::tt0;
  delete[] param::tt1;


  t0.stop();
  cout << "################################################################" << endl; 
  cout << "Total time: " << t0.getElapsedTimeInMicroSec()  << " us\t" << t0.getElapsedTimeInSec() << " s"  << endl; 
  cout << "################################################################" << endl; 

  exit(0);
}




//20H




