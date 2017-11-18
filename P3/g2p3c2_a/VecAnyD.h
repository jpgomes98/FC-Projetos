//GRUPO 2

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




  Vector& operator=( const Vector & r2 ); //iguala os vetores (ex:r3=r1)

  Vector operator+( const Vector & r2 ) const; //soma os vetores (ex:r1+r2)
  Vector operator+( const double a ) const; //soma a todos os elementos do vetor uma constante (ex:r1+a)
  friend Vector operator+( const double a, const Vector & r2 ); //soma novamente a todos os elementos do vetor uma constante (ex: a+r1)

  Vector operator-( const Vector & r2 ) const;//subtrai vetores (ex:r1-r2)
  Vector operator-( ) const; //nega o vetor (ex:-r1)

  Vector operator*( const double a ) const; //multiplca o vetor por um escalar (ex: r1*a) 
  friend Vector operator*( const double a, const Vector & r2 );//multiplica o vetor por um escalar novamente (ex:a*r2)


  double operator[](size_t i) const;
  double& operator[](size_t i);
  

  //friend Vector operator+( const Vector & r1, const Vector & r2 );
  friend std::ostream& operator<<( std::ostream& out, const Vector & r ); // operador para a escrita
		

  friend double dot( const Vector & r1, const Vector & r2 ); // função para o produto interno (ex:r1.r2)
  friend Vector med( const Vector & r1); // função para criar média dentro do vetor (ex:med(r1))

};

#endif
