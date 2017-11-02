//-----------------------------g0p2c0_main.cpp-------------------------------------------
// to solve the one-dimension Newton law 2nd order ODE 
// uses Runge-Kutta 
// and uses namespaces to feed parameters to fucntions and to return more variables

#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C

#include "g0p2c0_header.h"



  int main(){
    using namespace forF; // to include the parameter values
    using namespace forRK; // ti return more values from Runge-Kutta

    // reads the inputa data, for a test from the keyboard, later from a file
    std::cout<< "uses input keyboard data" << std::endl; // execution data, from the screen
    std::cout<< "parameters: mass m, constant k, friction la, strength f0, frequency w " << std::endl;
    std::cin >> m >> k >> la >> f0 >> w ; // physical parameters of the mass and force
    int n_max ; double h; // number of iterations  and time step
    std::cout<< "iteration parameters: number of iterations n_max, step h " << std::endl;
    std::cin >> n_max >> h ; // parameters of the strength
    double t0, x0, v0; // initial conditions
    std::cout<< "initial physical conditions: time t0, position x0, speed v0 " << std::endl;
    std::cin >> t0 >> x0 >> v0 ; 

    std::cout<< "uses output file data g0p2c0_out.txt" << std::endl; // output data, to files
    std::ofstream output("g0p2c0_out.txt");
    if ( output.fail() ) {
      std::cerr << "Impossíble to opne file " << std::endl;
      exit(1); // this terminates the process
    }
    else
      std::cout<< "file opens well" << std::endl;

    for(int n =0;  n < n_max; n++ ) { /* iterating cicle */
      double t1=  RuKuNew1(& Fovm,h,t0,x0,v0); //x1 and v1 are returned with the namespace
      std::cout << "x(" << n << ")= " << x0 << std::endl; 
      output << t0 << " " << x0 << " " << v0 << " " << n << std::endl;
      t0=t1; x0=x1; v0=v1;
    }

    return 0; 
  } 
