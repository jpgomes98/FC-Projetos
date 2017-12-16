#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>

using namespace std;

class Matrix{
  size_t n, m;
  double **mat;
  double det;

 public:
  explicit Matrix(size_t ncol, size_t nlin); /* Construtor por defeito */
  Matrix(const Matrix& M); /* Construtor por cópia */
  ~Matrix(); /* Destrutor */

  /* Funções que atuam sobre matrizes */
  
  void set(unsigned i, unsigned j, double a);  // definir o valor da casa ij da matriz para a
  size_t ncol() const;                         // output do numero de colunas, n
  size_t nlin() const;                         // output do numero de linhas, m
  void resize(unsigned new_n, unsigned new_m); // redimensionalizar a matriz
  Matrix invert();
  Matrix  transpose() const;                      // transpor a matrix original
  double  findDet();                              // calcular e definir o determinante. Imprime-o.



  /* Operadores */

  Matrix& operator=(const Matrix& M);
  Matrix& operator=(double a);
  Matrix operator+(const Matrix& M);
  Matrix  operator-(const Matrix& M);
  Matrix operator*(const Matrix& M);
  double operator()(unsigned i, unsigned j) const; // output do valor da casa ij
  double& operator()(unsigned i, unsigned j);    


  friend Matrix operator*(double a, const Matrix& M);
  friend Matrix operator/(const Matrix& M, double a);
  friend ostream& operator<<(ostream& out, const Matrix & r); // operador para escrita

  friend Matrix solve(Matrix& A, const Matrix& b);            // resolver a equação Ax = b
  

/** Operações especiais para vetores **/
  
  friend double dot(const Matrix& A, const Matrix& B);        // produto interno canónico
  friend Matrix cross(const Matrix& A, const Matrix& B);      // produto externo
  

};

#endif
