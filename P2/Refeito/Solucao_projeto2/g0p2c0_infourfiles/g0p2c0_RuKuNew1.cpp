//-----------------------------g0p2c0_RuKuNew.cpp-------------------------------------------
// to solve the one-dimension Newton law 2nd order ODE 
// uses Runge-Kutta 
// and uses namespaces to feed parameters to fucntions and to return more variables

#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C

#include "g0p2c0_header.h"



 namespace forRK{                    
    double x1, v1 ; // we would like the function to return this as well
  }


  double RuKuNew1( double (* Fovm)( double, double, double), double h, double t0, double x0, double v0){ // for Runge-Kutta 
    using namespace forRK; // this is equivalent to return x1 and v1 together with t1
    double t1;
    double k1x, k2x, k3x, k4x; 
    double k1v, k2v, k3v, k4v; 

    k1x = v0;
    k1v = Fovm ( x0 , v0, t0 );
    k2x = v0 + h* (.5* k1v);
    k2v = Fovm(  x0 + h* (.5* k1x), v0 + h* (.5* k1v) , t0 + (.5* h) );
    k3x =  v0 + h* (.5* k2v );
    k3v = Fovm(  x0 + h* (.5* k2x), v0 + h* (.5* k2v) , t0 + (.5* h) );
    k4x =  v0 + h* k3v ;
    k4v = Fovm(  x0 + h* k3x, v0 + h* k3v , t0 + h );

    t1 = t0 + h;
    x1 = x0 + (h/6.) *(k1x + 2.*k2x + 2.*k3x + k4x);
    v1 = v0 + (h/6.) *(k1v + 2.*k2v + 2.*k3v + k4v);
    // x1 = x0 + h * k1x; // to check with Euler
    // v1 = v0 + h * k1v; // to check with Euler
    return t1;
  }

