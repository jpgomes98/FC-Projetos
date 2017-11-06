//----------------------------g0p2c1.cpp---------------------------------
// to solve the three-dimension Newton law 2nd order system of ODEs
// uses Runge-Kutta 
// uses namespaces to feed parameters to fucntions and to return more variables
// also uses pointers to return arrays, and to feed arrays as arguments


#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C



  namespace forRK{                    
    double x1[3], v1[3] ; // we would like the function to return this as well
  }

  double RuKuNew3( double* (* Fovm3)( double[3], double[3], double), double h, double t0, double x0[3], double v0[3]){ // for Runge-Kutta 
/* here needed extra * and [3] in the arguments of the other function */
    using namespace forRK; // this is equivalent to return x1 and v1 together with t1
    double t1;
    double k1x[3], k2x[3], k3x[3], k4x[3]; 
    double k1v[3], k2v[3], k3v[3], k4v[3]; 
    double *pax;
    double xax[3], vax[3];

    pax = Fovm3 ( x0, v0, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k1x[i] = v0[i];
      k1v[i]= pax[i]; // to use the first array element, etc
      xax[i]= x0[i] + h* (.5* k1x[i]);
      vax[i]= v0[i] + h* (.5* k1v[i]);
    }

    pax = Fovm3 ( xax, vax, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k2x[i] = vax[i];
      k2v[i] = pax[i];  
      xax[i]= x0[i] + h* (.5* k2x[i]);
      vax[i]= v0[i] + h* (.5* k2v[i]);
    }

    pax = Fovm3 ( xax, vax, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k3x[i] = vax[i];
      k3v[i] = pax[i];  
      xax[i]= x0[i] + h* (.5* k3x[i]);
      vax[i]= v0[i] + h* (.5* k3v[i]);
    }

    pax = Fovm3 ( xax, vax, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k4x[i] = vax[i];
      k4v[i] = pax[i];  
      xax[i]= x0[i] + h* ( k4x[i]);
      vax[i]= v0[i] + h* ( k4v[i]);
    }


    t1 = t0 + h;
    for( int i=0; i<3; i++){
    x1[i] = x0[i] + (h/6.) *(k1x[i] + 2.*k2x[i] + 2.*k3x[i] + k4x[i]);
    v1[i] = v0[i] + (h/6.) *(k1v[i] + 2.*k2v[i] + 2.*k3v[i] + k4v[i]);
    // x1[i] = x0[i] + h * k1x[i]; // to check with Euler
    // v1[i] = v0[i] + h * k1v[i]; // to check with Euler
    }
    return t1;
  }


  namespace forF{
    double G, mt, rt, ms, ss,  ro, aa; // parameters of the strength
  }

  double* Fovm3( double x[3], double v[3], double t){ // for the acceleration 
    static double f[3]; // this needs to be static
    using namespace forF; // this should allow to include the parameters
    double fa[3],rr,vv;

    rr=sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    if(rr < rt){
      std::cout << " the satelite just hit the earth!! " << std::endl;
      exit(1); // this terminates the process
      }
    vv=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

    for(int i =0;  i < 3; i++ ){ 
      f[i]= - ((G*mt)/(rr*rr*rr))*x[i];
      fa[i]= (1./ms)*(- (.5 * ro*exp(-(rr-rt)/aa) * ss* vv))* v[i];
      f[i]=f[i]+fa[i];
    }

    return f;
  }   


  int main(){
    using namespace forF;    // to include the parameter values
    using namespace forRK;   // to return more values from Runge-Kutta

    // reads the input data, for a test from the keyboard, later from a file
    std::cout<< "uses input file data" << std::endl; // execution data, from the screen
    std::ifstream input("g0p2c1_inputsatelite.txt");
    std::cout<< "parameters: constan G,  earth mass mt, earth radius rt, satelite mass ms, satelite section ss, air ro, air decay aa " << std::endl;
    input >> G >> mt >> rt >> ms >> ss >> ro >> aa; // physical parameters of the mass and force
    int n_max, n_jump ; double h; // number of iterations  and time step, jump step for output
    std::cout<< "iteration parameters: number of iterations n_max, step h " << std::endl;
    input >> n_max >>  n_jump >> h ; // parameters of the strength
    double t0, x0[3], v0[3]; // initial conditions
    std::cout<< "initial physical conditions: time t0, position x0, speed v0 " << std::endl;
    input >> t0 >> x0[0] >> x0[1] >> x0[2] >> v0[0] >> v0[1] >> v0[2] ; 



    std::cout<< "uses output file data g0p2c0_out.txt" << std::endl; // output data, to files
    std::ofstream output("g0p2c1_out.txt");
    if ( output.fail() ) {
      std::cerr << "Impossíble to open file " << std::endl;
      exit(1); // this terminates the process
    }
    else
      std::cout<< "file opens well" << std::endl;

    for(int n =0;  n < n_max; n++ ) { /* iterating cicle */
      double t1=  RuKuNew3( &Fovm3,h,t0,x0,v0); //x1 and v1 are returned with the namespace, some of the arguments are arrays
            if( (n % n_jump) ==0 ){
        std::cout << "x[0]( t= " << t0 << ")= " << x0[0] << std::endl; 
        output << t0 << " " << x0[0] << " " << x0[1] << " " << x0[2] << " " << v0[0] << " " << v0[1] << " " << v0[2] << " " << sqrt(x0[0]*x0[0]+x0[1]*x0[1]+x0[2]*x0[2]) - rt << " " << sqrt(v0[0]*v0[0]+v0[1]*v0[1]+v0[2]*v0[2]) << std::endl;
      }
      t0=t1; 
      for( int i=0; i< 3; i++){
        x0[i] = x1[i];
        v0[i]= v1[i];
      }
    }

    return 0; 
  } 
