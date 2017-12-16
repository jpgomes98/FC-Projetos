#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include "dirent.h"

#include "Matrix.h"

using namespace std;

int main()
{
  /* Aux */
  double get;
  int y_n;
  bool plot_y_n;
  int systemReturn;

  /* Time Independent Schrördinger Equation - solução para um espaço infinito 1D (grid) */
  Matrix grid(1, 1);
  Matrix Energy(1, 1);
  Matrix waveFunc(1, 1);
  Matrix auxWave(waveFunc);
  int N;
  double limite;
  
  int nsol; // nº de soluções a calcular
  
  string toRead("inputschrodinger.txt");
  
  /* Setup dos ficheiros de escrita */
  string fname("schrodinger_");
  string fend(".dat");
  string complete;
  stringstream sstm;

  /* Setup gnuplot - 6 estados 
  string cmd_script("gnuplot -c multipleplot.plt ");
  string space(" ");
  string gnuplot;
  stringstream gstream;

  /* Setup gnuplot - Muitos estados 
  string plot_asmany("gnuplot -c plot_asmany.plt ");*/

  ifstream input;
  /* Stream para o plot */
  ofstream output;
  /* Stream para imprimir a matriz */
  ofstream outMatrix("outmatrix.txt");
  
  srand(time(NULL));

  /* Setup do input de modo a garantir que obtem o ficheiro com os parâmetros de inicialização */

  while (1)
    {
      if (checkDir(toRead)){
	input.open(toRead.c_str()); /* associar o stream 'input' ao filename contido no toRead;
				       contudo o ifstream só pode receber (const char*), pelo que   temos de converter a string numa C-string*/
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

  /************* Resolver a equação de Schrödinger para um potencial especifico ****************/

  cout << "*** Resolver a equação de Schrödinger num potencial específico ***" << "\n";
  cout << "Introduza a discretização do espaço pretendida (N_max): ";
  cin >> N;
  cout << "Introduza a fronteira do espaço a estudar (Lambda): ";
  cin >> limite;
  cout << "Pretende imprimir muitos estados (Sim - 1; Não - 0): ";
  cin >> plot_y_n;

  /* Impedir que o programa calcule todos os vetores próprios, apenas aqueles que o utilizador pretende */
  if (plot_y_n){
    cout << "Introduza o número de soluções que pretende: ";
    cin >> nsol;
  }
  else{
    cout << "O programa irá produzir gráficos dos 6 primeiros níveis de energia permitidos." << endl;
    nsol = 6;
  }
  
  /* Setup do output */
  sstm << fname << N << fend;
  complete = sstm.str();
  output.open(complete.c_str());
  /*******************/

  /* Inicializar vetores para guardar as energias calculadas (Energy) e a discretização do espaço (grid)*/
  
  Energy.resize(1, nsol);
  grid.resize(1, N);
  Energy = 0; 
  grid = 0;

  
  cout << "Parâmetros usados: " << endl;
  cout << " -> ħ = 1\n -> m = 1\n -> k = 1\n\n";
  cout << "A resolver..." << endl;

  /* Resolver a equação propriamente dita, para o potencial definido por moleculePotential */
  auxWave = solveSchrodinger(moleculePotential, Energy, grid, N, limite, nsol, input, outMatrix);
  
  /* auxWave é um objeto auxiliar que serve de intermédio para receber os vetores próprios calculados */
  
  waveFunc.resize(nsol, auxWave.nlin());
  waveFunc = 0;
  for (int j = 1; j <= nsol; j++){
    waveFunc.vec_in(j, auxWave.vec_out(j)); /* Obter os nsol menores valores próprios */
  }

  /* Output para um ficheiro para plot */
  for (int i = 1; i <= waveFunc.nlin(); i++){
    for (int j = 0; j <= waveFunc.ncol(); j++){
      if (j == 0){
	output << grid(i, 1) << " ";
      }
      else{
	if (j == waveFunc.ncol()){
	  output << waveFunc(i, j) << "\n";
	}
	else{
	  output << waveFunc(i, j) << " ";
	}
      }
    }
  }

  output.close();

  /* Elaborar o script gnuplot para o caso em que o utilizador se limita a querer 6 estados na mesma     imagem (0) ou 
     no caso em que o utilizador pretende muitos estados em múltiplos ficheiros */

  /*
  if (plot_y_n){
    gstream << plot_asmany << nsol;
  }
  else{
    gstream << cmd_script;
    for (int i = 1; i <= nsol; i++){
      gstream << Energy(i , 1) << space;
    }
  }
  
  gstream << "\n";
  gnuplot = gstream.str();
  */
  /*****************************/

  cout << "Funções onda (vetores próprios de H): ";
  cout << waveFunc;

  cout << "Energia dos primeiros " << nsol << " níveis: ";
  cout << Energy;
  cout << "Terminado" << endl;




  /* systemReturn = system(gnuplot.c_str());
  if(systemReturn == -1){
    cout << "Erro a invocar o gnuplot..." << endl;
    exit(EXIT_FAILURE);
  }
  else{
    cout << "gnuplot invocado com sucesso!" <<endl;
    cout << "Verifique os gráficos produzidos" << endl;
    }*/
  
  return 0;
}
