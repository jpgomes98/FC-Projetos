//-----------------------------g0p2c0_Fovm.cpp-------------------------------------------
// to solve the one-dimension Newton law 2nd order ODE 
// uses Runge-Kutta 
// and uses namespaces to feed parameters to fucntions and to return more variables

#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C

#include "g0p2c0_header.h"



  namespace forF{                    // unnamed or anonymous namespace
    double m, k, la, f0, w ; // parameters of the strength
  }


  double Fovm( double x, double v, double t){ // for the acceleration 
    using namespace forF; // this should allow to include the parameters
    double f= (- k *x) + (- la * v) + (f0 * sin (w * t));
    return (f/m);
  }  

