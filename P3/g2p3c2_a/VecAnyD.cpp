//---------- VecAnyD.cpp ----------
//GRUPO 2
#include <iostream>
#include "VecAnyD.h"



Vector::Vector(unsigned _len) : len(_len) { ptr = new double[len]; } 

Vector::Vector(const Vector& vec) : len(vec.len) {
  ptr = new double[len];
  for(unsigned i = 0; i < len; ++i) ptr[i] = vec.ptr[i];
}

Vector::~Vector() { delete[] ptr; }

unsigned Vector::size() const { return len; } 

double Vector::get(unsigned i) const { return ptr[i]; }

void Vector::set(unsigned i, double x) { ptr[i] = x; } 

double dot( const Vector & r1, const Vector & r2 ) { 
  unsigned _len = r1.size();
  double res = 0;
  for( unsigned i = 0; i < _len; ++i )
       res +=  r1.get(i) * r2.get(i);
  return res;
}

std::ostream& operator<<(std::ostream& out, const Vector& r)
{
  out << "(";
  for (unsigned i = 0; i < r.size(); ++i)
    if (i < r.size() - 1)
      out << r.get(i) << ", ";
    else
      out << r.get(i);
  out << ")";
  
  return out;
}

Vector& Vector::operator=( const Vector & r2 ){
  if(len != r2.size()) {
    std::cout << "size does not match!" << std::endl;
    delete[] ptr;
    len = r2.size();
    ptr = new double[len];
  }
  for(unsigned i = 0; i < len; ++i) ptr[i] = r2.ptr[i];
  return *this;
}


Vector Vector::operator+(const Vector & r2 ) const { // operador para a soma
  unsigned _len = size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, get(i) + r2.get(i)); 
  return ret;
}

Vector Vector::operator+(const double a ) const { // operador para a soma
  unsigned _len = size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, get(i) + a); 
  return ret;
}

Vector operator+(const double a, const Vector & r2 ) { // operador para a soma
  unsigned _len = r2.size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, a + r2.get(i)); 
  return ret;
}

Vector Vector::operator-(const Vector & r2 ) const { // operador para a diferença
  unsigned _len = size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, get(i) - r2.get(i)); 
  return ret;
}


Vector Vector::operator-() const {
  unsigned _len = size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, -get(i)); 
  return ret;
}

Vector Vector::operator*(const double a ) const { // operador para o produto por um escalar
  unsigned _len = size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, get(i)*a); 
  return ret;
  }

Vector operator*(const double a, const Vector & r2 ) { // operador para o produto por um escalar
  unsigned _len = r2.size();
  Vector ret(_len);
  for( unsigned i = 0; i < _len; ++i )
       ret.set(i, a*r2.get(i)); 
  return ret;
}

Vector med(const Vector & r1) { 
  unsigned _len = r1.size();
  Vector ret(_len);
  ret.set(0, r1.get(0));
  for( unsigned i = 1; i < _len-1; ++i )
    ret.set(i,(r1.get(i-1) + r1.get(i+1))/2);  
  ret.set(_len-1, r1.get(_len-1));
  return ret;
}

double Vector::operator[](size_t i) const { return ptr[i]; }

double& Vector::operator[](size_t i) { return ptr[i]; }


