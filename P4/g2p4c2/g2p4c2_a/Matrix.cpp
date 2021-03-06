#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "Matrix.h"


#define THRESHOLD 1e-6

using namespace std;

//Construtor por defeito
Matrix::Matrix(size_t ncol, size_t nlin): n(ncol), m(nlin)
{
  mat = new double*[m];

  for(int i=0; i < m; i++)
    {
      mat[i]=new double[n];
    }
}

//Construtor por cópia
Matrix::Matrix(const Matrix& M)
{
  n=M.n;
  m=M.m;

  mat = new double*[m];

  for(int i=0; i < m; i++)
    {
      mat[i]=new double[n];
    }

  for(int i=0; i < m; i++)
    {
      for(int j=0; j<n; j++)
      	{
      	  mat[i][j]=M.mat[i][j];
      	}
    }
}

//destrutor
Matrix::~Matrix()
{
  for(int i=0; i < m; i++)
    {
      delete[] mat[i];
    }
  delete[] mat;
}

//Funções------------------------------------------------------------------------------------

//Para definir o valor da casa ij da matriz para a
void Matrix::set(unsigned i, unsigned j, double a)
{
  if( ((i-1)>=m) || ((i-1)<0) || ((j-1)<0) || ((j-1)>=n))
    {
      cout << "Essa componente não existe!"<< endl;
      exit(EXIT_FAILURE);
    }
    else
    {
      mat[i-1][j-1]=a;
    }
}

//retorna o número de colunas e linhas
size_t Matrix::ncol() const { return n;}

size_t Matrix::nlin() const { return m;}

//Para mudar o tamanho da matriz
void Matrix::resize(unsigned new_n, unsigned new_m)
{
  for(int i=0; i < m; i++)
    {
      delete[] mat[i];
    }
  delete[] mat;

  n= new_n;
  m= new_m;
  
  mat = new double*[m];
  for(int i=0; i < m; i++)
    {
      mat[i]=new double[n];
    }
}
//Para inverter a matriz
Matrix Matrix::invert()
{
  double c=0;
  double det=1;

  if (n!=m)
  {
    cout<< "A matriz não é quadrada logo não é invertível."<< endl;
    exit(EXIT_FAILURE);
  }

  else
  {
    //Matriz identidade
    Matrix Identity(n, m);
    Identity=0; //Define a matriz identidade 

    for(int i=0; i<Identity.nlin(); i++)
    {
      Identity.mat[i][i]=1;
    } 

    Matrix T(*this); //passa por cópia a matriz

    for(int i=0; i<(T.m-1); i++) //percorre linhas exceto a última e faz "eliminação de gauss"
    {
      for(int k=(i+1); k<T.m; k++) //percorre as linhas seguintes
      {
        if(T.mat[i][i] == 0)
        {
          cout << "Esta matriz é singular logo não é invertível." << endl;
          cout << "Determinante=0" << endl;

          return *this;
        }

        else
        {
          c=((double)T.mat[k][i]/(double)T.mat[i][i]);

          for(int j=0; j<T.n; j++)
          {
            T.mat[k][j]=T.mat[k][j]-c*T.mat[i][j];
            Identity.mat[k][j]=Identity.mat[k][j]-c*Identity.mat[i][j];
          }
        }

      }
    }

    for (int i = 0; i < T.m; i++) //Calcula o determinante
    {
      det *= T.mat[i][i]; //multiplica todos os valores que estão na diagonal principal
    }

    for(int i=(T.n-1); i>0; i--) //percorre linhas a começar do fim exceto a primeira e faz "eliminação de gauss"
    {
      for(int k=(i-1); k>=0; k--) //percorre as linhas anteriores
      {
        c=((double)T.mat[k][i]/(double)T.mat[i][i]);

        for(int j = (T.m - 1); j >= 0; j--)
        {
          T.mat[k][j] = T.mat[k][j] - c*T.mat[i][j];
          Identity.mat[k][j] = Identity.mat[k][j] - c*Identity.mat[i][j];
        }

      }
    }

    for(int i=0; i<T.n; i++) //divide toda a linha da diagonal pelo valor necessário
    {
      c=(1./(double)T.mat[i][i]);

      for(int j=0; j<T.n; j++)
      {
        T.mat[i][j] = c* T.mat[i][j];
        Identity.mat[i][j] = c*Identity.mat[i][j];
      }
    }


    cout<< "\nA matriz inverteu!"<< endl;
    cout<< "Determinante="<< det <<endl;
    return Identity;
  }
}

Matrix Matrix::transpose() const
{
  Matrix T(*this);
  if (n != m){
    T.resize(m, n);
  }
  for (int i = 1; i <= T.nlin(); i++){
    for (int j = 1; j <= T.ncol(); j++){
      T.set(i, j, mat[j - 1][i - 1]);
    }
  }

  return T;
}

double Matrix::findDet()
{
  /* Cálculo do determinante pelo Método de Eliminação de Gauss */
  /* Obter matriz em escada de linhas */

  if(n != m){
    cout << "A matriz tem dimensões " << m << "x" << n << ". Não é quadrada, pelo que não tem determinante definido!" << endl;
    det = nan("");
  }

  else{
    Matrix T(*this); // tabalhar com uma cópia
    double c = 1;
  
    for (int i = 0; i < (T.m - 1) ; i++){              // linha atual que está a ser usada para eliminar
      for (int k = (i + 1); k < T.m; k++){             // percorrer as linhas seguintes àquela que foi está selecionada
  if (T.mat[i][i] == 0){                               //  Verificar se o rank = nº colunas 
    det = 0;
  }
  else {
    c = ((double) T.mat[k][i]) / ((double) T.mat[i][i]); // coeficiente de eliminação
    for (int j = 0; j < T.n; j++){
      T.mat[k][j] = T.mat[k][j] - c * T.mat[i][j];
      // percorrer a linha a subtrair a atual multiplicada por um fator c
    }
  }
      }
    }

    /* Calcular o determinante */

    for (int i = 0; i < T.m; i++){
      det *= T.mat[i][i];
    }
  }
  return det;
}

//Operadores---------------------------------------------------------------------------

Matrix& Matrix::operator=(const Matrix& M)
{

  if (this == &M){
    return *this;
  }

  else
    {
      if( (m != M.m) || (n !=M.n))
      	{
      	  this -> resize(M.n, M.m);
      	}
            
      for(int i =0; i< m; i++)
      	{
      	  for(int j = 0; j<n; j++)
      	    {
      	      mat[i][j]=M.mat[i][j];
      	    }
      	}
      return *this;
    }
}

Matrix& Matrix::operator=(double a)
{
  for(int i=0; i<m; i++)
    {
      for(int j=0; j<n; j++)
	{
	  mat[i][j]=a;
	}
    }
  return *this;
}

Matrix Matrix::operator+(const Matrix& M)
{
  if((n==M.n) && (m==M.m))
    {
      Matrix resulta(n,m);
      resulta=0;

      for(int i=0; i<resulta.n; i++)
      	{
      	  for(int j=0; j<resulta.m; j++)
      	    {
      	      resulta.mat[i][j]=mat[i][j]+M.mat[i][j];
      	    }
      	}
      return resulta;
    }
  else
    {
      cout<< "Estas matrizes não são somáveis."<<endl;
      exit(EXIT_FAILURE);
    }
}


Matrix Matrix::operator-(const Matrix& M)
{
  if ((n == M.n) && (m == M.m)){
    Matrix result(n, m); // A matriz resultante tem o número de colunas da 2º e o número de linhas da 1º
    result = 0;
    for (int i = 0; i < result.m; i++){
      for (int j = 0; j < result.n; j++){
  result.mat[i][j] = mat[i][j] - M.mat[i][j];
      }
    }
    return result;
  }
  else{
    cout << "Matrizes não subtraíveis!" << endl;
    exit(EXIT_FAILURE);
  }
}


Matrix Matrix::operator*(const Matrix & M)
{
  //Verificação da possibilidade de multiplicação
  if(n == M.m)
    {
      Matrix result(M.n, m);
      result = 0;

      for(int i=0; i<result.m; i++)
      	{
      	  for(int j=0; j<result.n; j++)
      	    {
      	      for(int k=0; k<n; k++)
            		{
            		  result.mat[i][j] += mat[i][k]*M.mat[k][j];
            		}
      	    }
      	}

      return result;
    }

  else
    {
      cout<< "Não é possível a multiplicação.\n As matrizes têm tamanhos não compatíveis."<<endl;
      exit(EXIT_FAILURE);
    }

}

double Matrix::operator()(unsigned i, unsigned j) const
{
   if (((i-1) >= m) || ((j-1) >= n) || ((i-1) < 0) || ((j-1) < 0))
    {
      cout << "A matriz em questão não tem esse elemento." << endl;
      cout << "Não foi possível aceder ao valor dessa casa" << endl;
      exit(EXIT_FAILURE);
    }
   else{
     return mat[i-1][j-1];
   }
}

double& Matrix::operator()(unsigned i, unsigned j)
{
  if (((i-1) >= m) || ((j-1) >= n) || ((i-1) < 0) || ((j-1) < 0))
    {
      cout << "A matriz em questão não tem esse elemento." << endl;
      cout << "Não foi possível aceder ao valor dessa casa" << endl;
      exit(EXIT_FAILURE);
    }
   else{
     return mat[i-1][j-1];
   }
}


Matrix operator*(double a, const Matrix& M)
{
  Matrix Ret(M); //matrix de retorno
  for (int i = 0; i < M.m; i++){
    for (int j = 0; j < M.n; j++){
      Ret.mat[i][j] *= a;
    }
  }

  return Ret;
}

Matrix operator/(const Matrix& M, double a)
{
  Matrix Ret(M); //matrix de retorno
  for (int i = 0; i < M.m; i++){
    for (int j = 0; j < M.n; j++){
      Ret.mat[i][j] /= a;
    }
  }

  return Ret;
}


ostream& operator<<(ostream& out, const Matrix& r)
{
  cout << endl;
  
  for( unsigned i = 1; i <= r.nlin(); ++i ){
    for (unsigned j = 1; j <= r.ncol(); ++j)
      {
      	if (abs(r(i,j)) <= THRESHOLD)
        { // controlo de precisão
          out << 0 << " ";
        }
        else 
          {
            out << r(i,j) << " ";
          }
        }

    out << "\n";
  
  }
  cout << endl;
  
  return out;
}

Matrix solve(Matrix& A, const Matrix& b) {
  if (A.ncol() != A.nlin()){
    cout << "O sistema representado pela matriz em questão não tem característica máxima. Procure resolver a equação por outro método" << endl;
    exit(EXIT_FAILURE);
  }
  else if (A.ncol() != b.nlin()){
    cout << "O sistema representado pela matriz em questão não tem característica máxima. Procure resolver a equação por outro método" << endl;
    cout << "Neste caso, o vetor b tem um número de coeficientes diferente do número de linhas da matriz A" << endl;
    exit(EXIT_FAILURE);
  }
  else{
    Matrix x(A.nlin(), b.ncol());
    x = A.invert() * b;
    return x;
  }
}


double dot(const Matrix& A, const Matrix& B){
  // Testar se são vetores
  double val = 0;
  int a = 0, b = 0;
  /* Matrizes de correção - podem ter qualquer dimensão */
  Matrix At(1, 1);
  Matrix Bt(1, 1);
  if (((A.nlin() > 1) && (A.ncol() > 1)) || (((B.nlin() > 1) && (B.ncol() > 1)))){
      cout << "Os objetos apresentados não são vetores. O produto interno não está definido." << endl;
      val = nan("");
  }
  else{

    if (((A.nlin() == B.nlin()) || (A.ncol() == B.ncol()))){
      /* Corrigir a posição dos vetores para ficar na forma a . b = a^T.b */
      if (B.ncol() == 1){
  At = A.transpose();
  Bt = B;
      }

      else if(A.nlin() == 1){
  Bt = B.transpose();
  At = A;
      }
    }

    else if((A.nlin() == B.ncol()) && (A.ncol() == 1)){ /* Quando estão todos ao contrário. A 2º condição serve para distinguir da seguinte */
      At = A.transpose();
      Bt = B.transpose();
    }

    else if(A.ncol() == B.nlin()){ /** Tudo ok **/
      At = A;
      Bt = B;
    }
  }

  
  /* Efetuar o cálculo */
  if ((At.nlin() == 1) && (Bt.ncol() == 1) && (At.ncol() == Bt.nlin())){
    for (int i = 1; i <= At.ncol(); i++){
      val += At(1, i) * Bt(i, 1);
    }
  }

  else{
    cout << "As dimensões dos vetores em questão são incompatíveis." << endl;
    val = nan("");
  }

  return val;
}

Matrix cross(const Matrix& A, const Matrix& B)
{
  Matrix Ext(1, 3); // O resultado será sempe um vetor coluna em R³
  if (((A.nlin() > 1) && (A.ncol() > 1)) || (((B.nlin() > 1) && (B.ncol() > 1)))){
    cout << "Os objetos apresentados não são vetores. O produto externo não está definido." << endl;
    exit(EXIT_FAILURE);
  }

  else if (((A.nlin() + A.ncol()) != 4 && (A.nlin() != 3)) || ((B.nlin() + B.ncol()) != 4 && (B.nlin() != 3))){
    cout << "Os vetores têm de estar em R³ para se efetuar o produto externo." << endl;
    cout << "Apenas vetores coluna poderão ser usados para calcular um produto externo." << endl;
    exit(EXIT_FAILURE);
  }

  else{
    Ext.set(1,1, A(2,1) * B(3,1) - A(3,1)*B(2,1));
    Ext.set(2,1, A(3,1) * B(1,1) - A(1,1)*B(3,1));
    Ext.set(3,1, A(1,1) * B(2,1) - A(2,1)*B(1,1));
  }

  return Ext;
}

