//----------------------------g0p2c2.cpp---------------------------------
// to solve the three-dimension Newton law 2nd order system of ODEs
// uses Runge-Kutta 
// uses namespaces to feed parameters to fucntions and to return more variables
// also uses pointers to return arrays, and to feed arrays as arguments


#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C




struct Vec {                        // simple structure for 3-d arrays/vectors
  double el[3];                     // the matrix elements 
  Vec() {                           // default constructor
    el[0] = el[1] = el[2] = 0.;     // inicializing variables
  }
  Vec(double _x, double _y, double _z) { // standard construtor,
    el[0] = _x;                    // convenient to work with the matriz elements
    el[1] = _y;
    el[2] = _z;
  }
  Vec(double _el[3]) {              // standard construtor,
    el[0] = _el[0];                 // convenient to work with the matriz elements
    el[1] = _el[1];
    el[2] = _el[2];
  }
  double get(int n) const { return el[n];}  // to return matrix elements
  double* get() {return el;}        // to work with arrays
  void print(){ std::cout << el[0] << "\t" << el[1] << "\t" << el[2] << std::endl; } // for a fast output
  
  ~Vec (){}                        // standard destructor
};



  namespace forRK{                    
    Vec x1, v1 ; // we would like the function to return this as well
  }

  double RuKuNew3( Vec (* Fovm3)( Vec, Vec, double), double h, double t0, Vec x0, Vec v0){ // for Runge-Kutta 
/* here needed extra * and [3] in the arguments of the other function */
    using namespace forRK; // this is equivalent to return x1 and v1 together with t1
    double t1;
    Vec k1x, k2x, k3x, k4x; 
    Vec k1v, k2v, k3v, k4v; 
    Vec pax;
    Vec xax, vax;

    pax = Fovm3 ( x0, v0, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k1x.el[i] = v0.el[i];
      k1v.el[i]= pax.el[i]; // to use the first array element, etc
      xax.el[i]= x0.el[i] + h* (.5* k1x.el[i]);
      vax.el[i]= v0.el[i] + h* (.5* k1v.el[i]);
    }

    pax = Fovm3 ( xax, vax, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k2x.el[i] = vax.el[i];
      k2v.el[i] = pax.el[i];  
      xax.el[i]= x0.el[i] + h* (.5* k2x.el[i]);
      vax.el[i]= v0.el[i] + h* (.5* k2v.el[i]);
    }

    pax = Fovm3 ( xax, vax, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k3x.el[i] = vax.el[i];
      k3v.el[i] = pax.el[i];  
      xax.el[i]= x0.el[i] + h* (.5* k3x.el[i]);
      vax.el[i]= v0.el[i] + h* (.5* k3v.el[i]);
    }

    pax = Fovm3 ( xax, vax, t0 ); // some of the arguments are arrays
    for( int i=0; i<3; i++){
      k4x.el[i] = vax.el[i];
      k4v.el[i] = pax.el[i];  
      xax.el[i]= x0.el[i] + h* ( k4x.el[i]);
      vax.el[i]= v0.el[i] + h* ( k4v.el[i]);
    }


    t1 = t0 + h;
    for( int i=0; i<3; i++){
    x1.el[i] = x0.el[i] + (h/6.) *(k1x.el[i] + 2.*k2x.el[i] + 2.*k3x.el[i] + k4x.el[i]);
    v1.el[i] = v0.el[i] + (h/6.) *(k1v.el[i] + 2.*k2v.el[i] + 2.*k3v.el[i] + k4v.el[i]);
    // x1.el[i] = x0.el[i] + h * k1x.el[i]; // to check with Euler
    // v1.el[i] = v0.el[i] + h * k1v.el[i]; // to check with Euler
    }
    return t1;
  }


  namespace forF{                    
    double G, mt, rt, ms, ss,  ro, aa; // parameters of the strength
  }

  Vec Fovm3( Vec x, Vec v, double t){ // for the acceleration 
    Vec f, fa; // this needs to be static
    using namespace forF; // this should allow to include the parameters
    double rr,vv;

    rr=sqrt(x.el[0]*x.el[0]+x.el[1]*x.el[1]+x.el[2]*x.el[2]);
    if(rr < rt){
      std::cout << " the satelite just hit the earth!! " << std::endl;
      exit(1); // this terminates the process
      }
    vv=sqrt(v.el[0]*v.el[0]+v.el[1]*v.el[1]+v.el[2]*v.el[2]);

    for(int i =0;  i < 3; i++ ){ 
      f.el[i]= - ((G*mt)/(rr*rr*rr))*x.el[i];
      fa.el[i]= (1./ms)*(- (.5 * ro*exp(-(rr-rt)/aa) * ss* vv))* v.el[i];
      f.el[i]=f.el[i]+fa.el[i];
    }
/* check
std::cout << "f " << x[0] << "  " << x[1] << "  " << x[2]<<std::endl;    
std::cout << "f " << fa[0] << "  " << fa[1] << "  " << fa[2]<<std::endl;    
std::cout << "f " << G*mt << " " << pow((x[0]*x[0]+x[1]*x[1]+x[2]*x[2]),1.5) << " " << x[0] << " " << ((G*mt)/pow((x[0]*x[0]+x[1]*x[1]+x[2]*x[2]),1.5))*x[0] <<std::endl;   
std::cout << "f " << " " <<  ms << " " <<  aa << " " << ro << " " << v[1] <<std::endl;   
*/ 

    return f;
  }   


  int main(){
    using namespace forF; // to include the parameter values
    using namespace forRK; // ti return more values from Runge-Kutta

    // reads the input data, for a test from the keyboard, later from a file
    std::cout<< "uses input file data" << std::endl; // execution data, from the screen
    std::ifstream input("g0p2c1_inputsatelite.txt");
    std::cout<< "parameters: constan G,  earth mass mt, earth radius rt, satelite mass ms, satelite section ss, air ro, air decay aa " << std::endl;
    input >> G >> mt >> rt >> ms >> ss >> ro >> aa; // physical parameters of the mass and force
    int n_max, n_jump ; double h; // number of iterations  and time step, jump step for output
    std::cout<< "iteration parameters: number of iterations n_max, step h " << std::endl;
    input >> n_max >>  n_jump >> h ; // parameters of the strength
    double t0;
    Vec x0, v0; // initial conditions
    std::cout<< "initial physical conditions: time t0, position x0, speed v0 " << std::endl;
    input >> t0 >> x0.el[0] >> x0.el[1] >> x0.el[2] >> v0.el[0] >> v0.el[1] >> v0.el[2] ; 



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
        std::cout << "x.el[0]( t= " << t0 << ")= " << x0.el[0] << std::endl; 
        output << t0 << " " << x0.el[0] << " " << x0.el[1] << " " << x0.el[2] << " " << v0.el[0] << " " << v0.el[1] << " " << v0.el[2] << " " << sqrt(x0.el[0]*x0.el[0]+x0.el[1]*x0.el[1]+x0.el[2]*x0.el[2]) - rt << " " << sqrt(v0.el[0]*v0.el[0]+v0.el[1]*v0.el[1]+v0.el[2]*v0.el[2]) << " " << n << std::endl;
      }
      t0=t1; 
      for( int i=0; i< 3; i++){
        x0.el[i] = x1.el[i];
        v0.el[i]= v1.el[i];
      }
    }

    return 0; 
  } 
