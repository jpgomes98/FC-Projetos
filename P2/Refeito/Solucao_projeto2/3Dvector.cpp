//----------------------------3Dvector.cpp---------------------------------
// structure to define a type of 3 dimension vectors
// inspired in the structure Point defined in the slides of aula 3 of FC, DF, IST


#include <iostream> // to in and out from the kerboard and to the screen



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


 
  Vec testfun( double x){         // testing: a function of type Vec   
    Vec ccc(2.+x,3.,4.);
    return ccc;
  }

  Vec testlala( Vec vv){          // testing: a function of argument Vec
    Vec ccc(2.+vv.el[0],3.+vv.el[1],4.+vv.el[2]);
    return ccc;
  }


    
  int main(){

    Vec bbb(1.,2.,3.);            // initializing a vector 
    std::cout << bbb.el[0] << std::endl;
    std:: cout << bbb.get(0) << std::endl;
    bbb.print();
    std::cout << testfun(2).el[0] << std::endl;
    std::cout << testlala(bbb).el[0] << std::endl;
 
    Vec ccc;                     // initializing with another vector
    ccc=bbb;
    ccc.print();


    double *aa;                  // directly working with an array;
    aa = bbb.get();
    double *dd = new double[3];
    

                                 // NEVERTHELESS for operations we still need a cycle to work with all matrix elements
    for(int i=0; i<3; i++) {
      ccc.el[i]=aa[i]+ 2. * bbb.el[i];
      dd[i]= (ccc.el[i] / bbb.el[i]) + aa[i];
    }
    ccc.print();
    std::cout << dd[0] << std::endl;


    delete[] dd;

  
    return 0; 
  } 
