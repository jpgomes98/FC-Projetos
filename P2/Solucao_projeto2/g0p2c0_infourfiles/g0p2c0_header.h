//-----------------------------g0p2c0_header.h-------------------------------------------
// to solve the one-dimension Newton law 2nd order ODE 
// uses Runge-Kutta 
// and uses namespaces to feed parameters to fucntions and to return more variables
//
// header for the main function

#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out wehaderith files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C

// header for main

  double RuKuNew1( double (* Fovm)( double, double, double), double h, double t0, double x0, double v0); // for Runge-Kutta , used in main
  double Fovm( double x, double v, double t); // for the acceleration, used in RuKuNew1 and in main


  namespace forRK{         // to be used by this namespace         
    extern double x1, v1 ; // extern because the variable is defined elsewhere
  }

  namespace forF{                    // to be used by this namespace
    extern double m, k, la, f0, w ; // extern because  the variable is defined elsewhere
  }

