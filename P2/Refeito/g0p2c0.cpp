//-----------------------------g0p2c0.cpp-------------------------------------------
// to solve the one-dimension Newton law 2nd order ODE 
// uses Runge-Kutta 
// and uses namespaces to feed parameters to fucntions and to return more variables

#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C

using namespace std;

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

  namespace forF{                    
    double m, k, la, f0, w ; // parameters of the strength
  }
  double Fovm( double x, double v, double t){ // for the acceleration 
    using namespace forF; // this should allow to include the parameters
    double f= (- k *x) + (- la * v) + (f0 * sin (w * t));
    return (f/m);
  }  

  int main(){
    using namespace forF; // to include the parameter values
    using namespace forRK; // ti return more values from Runge-Kutta

    // reads the inputa data, for a test from the keyboard, later from a file
    cout<< "uses input keyboard data" << endl; // execution data, from the screen
    cout<< "parameters: mass m, constant k, friction la, strength f0, frequency w " << endl;
    cin >> m >> k >> la >> f0 >> w ; // physical parameters of the mass and force
    int n_max ; double h; // number of iterations  and time step
    cout<< "iteration parameters: number of iterations n_max, step h " << endl;
    cin >> n_max >> h ; // parameters of the strength
    double t0, x0, v0; // initial conditions
    cout<< "initial physical conditions: time t0, position x0, speed v0 " << endl;
    cin >> t0 >> x0 >> v0 ; 

    cout<< "uses output file data g0p2c0_out.txt" << endl; // output data, to files
    ofstream output("g0p2c0_out.txt");
    if ( output.fail() ) {
      cerr << "Impossíble to opne file " << endl;
      exit(1); // this terminates the process
    }
    else
      cout<< "file opens well" << endl;

    for(int n =0;  n < n_max; n++ ) { /* iterating cicle */
      double t1 =  RuKuNew1(&Fovm,h,t0,x0,v0); //x1 and v1 are returned with the namespace
      cout << "x(" << n << ")= " << x0 << endl; 
      output << t0 << " " << x0 << " " << v0 << " " << n << endl;
      t0=t1; x0=x1; v0=v1;
    }

    return 0; 
  } 
