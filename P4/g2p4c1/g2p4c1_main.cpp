#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>

#include "dirent.h"
#include "Matrix.h"

using namespace std;

int main()
{
  /* Aux */
  double get;
  int y_n;

  /* Time Independent Schrödinger Equation - construção do operador Hamiltoniano */
  int N;
  double limite;

  /* Inicializar o operador H */
  Matrix H(1,1);

  /* Inicializar a rede unidimensional */
  Matrix grid(1,1);
  
  /* Parâmetros físicos do problema */
  /* Para Schrodinger */
  double h_bar;
  double m;

  /* Para o potencial */
  double k;
  double a;
  double b;

  /* Parâmetros computacionais */
  double step;  // step de rede
  double par;   // parâmetro 

  /* Input */
  string toRead("inputschrodinger.txt");
  ifstream input;
  
  /* Stream para imprimir a matriz */
  ofstream outMatrix("outmatrix.txt");

  srand(time(NULL));

  /* Setup do input de modo a garantir que obtem o ficheiro com os parâmetros de inicialização */
  while (1)
    {
      if (checkDir(toRead)){
	input.open(toRead.c_str());

	/* associar o stream 'input' ao filename contido no toRead;
           contudo o ifstream só pode receber (const char*), pelo que  
	   temos de converter a string numa C-string*/
	
	if (input.is_open()){
	  break;
	}
	else{
	  cout << "Erro..." << endl;
	  exit(EXIT_FAILURE);
	}
      }
      else{
	cout << "O ficheiro com os dados necessários à inicialização não se encontra na  diretória atual." << endl;
	cout << "Pretende especificar um novo ficheiro de leitura? (Sim - 1, Não - 0) " << endl;
	cin >> y_n;
	if (y_n == 1){
	    cout << "Indique o novo ficheiro: ";
	    cin.clear();
	    cin.ignore(80, '\n');
	    getline(cin, toRead);

	  }
	else{
	  cout << "Terminado." << endl;
	  return 1;
	}
      }
    }

  /* Ler do ficheiro de input */
  input >> k >> a >> b >> m >> h_bar >> N >> limite;

  /************* Definir o operador H ****************/

  cout << "*** Operador Hamitoniano ***" << "\n\n";
  cout << "Discretização do interior do espaço pretendida (N_max): " << N << endl;
  cout << "Introduza a fronteira do espaço a estudar (Lambda): " << limite << endl;

  H.resize(N, N); // redifinir o Hamiltoniano para tomar a forma H = K + V(x)
  grid.resize(1, N);      // redifinir o tamanho da rede unidimensional - de -4 a 4 são 9 pontos que é o número de pontos discretizados

  /* Definir os parâmetros computacionais */

  step = 2. * limite / (N + 1); // step de rede
  par = (h_bar * h_bar) / (2. * m * step * step); 

  /* Definir a rede unidimensional */
  for (int i = 1; i <= grid.nlin(); i++){
    grid.set(i, 1, (-1) * limite + i * step);
  }

  cout << grid;

  /* Definir a matriz hamiltoniana */
  H = 0;

  for (int i = 1; i <= H.nlin(); i++){
    for (int j = (i - 1); j < (i + 2); j++){
      if ((i == 1) && (j == 0)){
	j++;
      }

      if ((i == H.nlin()) && (j == H.ncol() + 1)){
	break;
      }
	
      if (i == j){
	/* Preencher a diagonal principal */
	H.set(i, i, 2 * par + moleculePotential(a, b, k, grid(i, 1)));
      }
      else{
	/* Preencher as restantes duas diagonais acima e abaixo da principal */
	H.set(i, j, (-1) * par);
      }
    }
  }

  cout << "Verificação de que é simétrica (1 - é simetrica, 0 - não é): " << H.isSymmetric() << endl;

  cout << H << "\n";

  /* Imprimir a matriz H para um ficheiro */
  cout << "Enviando a matriz H para um ficheiro...\n\n";
  if(outMatrix.is_open()){
    outMatrix << H;
    cout << "Matriz enviada! Procure o ficheiro 'outmatrix.txt'." << endl; 
  }
  else{
    cout << "Há algum problema com o ficheiro 'outmatrix.txt'..." << endl;
    return -1;
  }
  
  return 0;
}
