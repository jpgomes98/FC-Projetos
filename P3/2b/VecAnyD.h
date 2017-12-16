#ifndef VECANYD_H
#define VECANYD_H

//---------- VecAnyD.h ----------
#include <iostream>

class Vector {
  private:
  unsigned len;
  double *ptr;
  public:
  //construtor standard 
  explicit Vector(unsigned _len); // explicit proíbe usar = na construção
  Vector(const Vector& vec); //construtor por cópia
  ~Vector(); //Destrutor
  unsigned size() const; //lê a dimensão (número de elementos)do vetor
  double get(unsigned i) const; //lê elemento i do vetor
  void set(unsigned i,double x); //altera elemento i do vetor para x




  Vector& operator=( const Vector & r2 ); 
  Vector& operator=( const double a ); 

  Vector operator+( const Vector & r2 ) const;
  Vector operator+( const double a ) const;
  friend Vector operator+( const double a, const Vector & r2 );
  friend Vector operator*( const double a, const Vector & r2 );

  Vector operator-( const Vector & r2 ) const;
  Vector operator-( ) const;

  double operator[](size_t i) const;
  double& operator[](size_t i);

  friend Vector med(const Vector& r2);
  friend Vector vecD2(const Vector& r2);
  friend double SumAbsDif(const Vector& r1, const Vector& r2);
  

  //friend Vector operator+( const Vector & r1, const Vector & r2 );
  friend std::ostream& operator<<( std::ostream& out, const Vector & r ); // operador para a escrita
		

  friend double dot( const Vector & r1, const Vector & r2 ); // função para o produto interno

};

#endif
