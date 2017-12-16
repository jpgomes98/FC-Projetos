/* FC - Ex.3 - Projeto 4*/

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

  /* Time Independent Schrödinger Equation - solução para um espaço infinito 1D (grid) */
  Matrix grid(1, 1);
  Matrix Energy(1, 1);
  Matrix waveFunc(1, 1);
  Matrix auxWave(waveFunc);

  /* Parâmetros recebidos mais à frente */
  int N;
  double limite;
  int nsol; // nº de soluções a calcular

  /* Parâmetros físicos */
  /* Eq. Schrödinger */
  double h_bar;
  double m;

  /* Potencial */
  double k;
  double a;
  double b;
  
  string toRead("inputschrodinger.txt");
  
  /* Setup dos ficheiros de escrita para indicarem o numero de pontos usados N */
  string fname("schrodinger_");
  string fend(".dat");
  string complete;
  stringstream sstm;

  /* Setup gnuplot - 6 estados */
  string cmd_script("gnuplot -c multipleplot.plt ");
  string space(" ");
  string gnuplot;
  stringstream gstream;


  ifstream input;
  /* Stream para o plot direto */
  ofstream output;

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

  cout << "*** Resolver a equação de Schrödinger num potencial específico ***" << "\n\n";

  
  /* Ler do ficheiro de input os parâmetros necessários */
  input >> k >> a >> b >> m >> h_bar >> N >> limite;
  
  cout << "Discretização do espaço (N_max): " <<  N << endl;
  cout << "Fronteira do espaço a estudar (Lambda): " << limite << "\n\n";
  cout << "Pretende imprimir mais do que 4 vetores próprios (Sim - 1; Não - 0): ";
  cin >> plot_y_n;
  cout << "\n";

  /* Impedir que o programa calcule todos os vetores próprios, apenas aqueles que o utilizador pretende */
  if (plot_y_n){
    cout << "Introduza então o número de soluções que pretende: ";
    cin >> nsol;
    cout << "\n";
  }
  else{
    cout << "O programa irá produzir gráficos dos 4 primeiros níveis de energia permitidos." << endl;
    nsol = 4;
  }
  
  /* Setup do output para um ficheiro que indica o número de discretizações */
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
  cout << " -> ħ = " << h_bar << "\n";
  cout << " -> m = " << m << "\n";
  cout << " -> k = " << k << "\n";
  cout << " -> a = " << a << "\n";
  cout << " -> b = " << b << "\n\n";

  /* Resolver a equação propriamente dita, para o potencial definido por moleculePotential */
  auxWave = solveSchrodinger(moleculePotential, Energy, grid, N, limite, nsol, h_bar, m, a, b, k);
  
  /* auxWave é um objeto auxiliar que serve de intermédio para receber os vetores próprios calculados */
  
  waveFunc.resize(nsol, auxWave.nlin());
  waveFunc = 0;
  for (int j = 1; j <= nsol; j++){
    waveFunc.vec_in(j, auxWave.vec_out(j)); /* Obter os 'nsol' menores valores próprios */
  }

  /* Output para um ficheiro para plot */
  for (int i = 1; i <= waveFunc.nlin(); i++){
    for (int j = 0; j <= waveFunc.ncol(); j++){
      if (j == 0){
	/* Print das discretizações */
	output << grid(i, 1) << " ";
      }
      else{
	if (j == waveFunc.ncol()){
	  /* Print das componentes dos vetores próprios */
	  output << waveFunc(i, j) << "\n";
	}
	else{
	  output << waveFunc(i, j) << " ";
	}
      }
    }
  }

  output.close();

  /* Elaborar o script gnuplot para o caso em que o utilizador se limita a querer 6 estados na mesma     imagem - esta rotina seguinte permite invocar o gnuplot na parte final do programa */
 
  gstream << cmd_script;
  for (int i = 1; i <= nsol; i++){
    gstream << space;
  }
  gstream << "\n";
  gnuplot = gstream.str();
  
  /*****************************/

  /*  cout << "Funções onda (vetores próprios de H): ";
      cout << waveFunc;*/

  cout << "Energia dos primeiros " << nsol << " níveis: ";
  cout << Energy;
  cout << "Terminado" << endl;



  systemReturn = system(gnuplot.c_str());
  if(systemReturn == -1){
    cout << "Erro a invocar o gnuplot..." << endl;
    exit(EXIT_FAILURE);
  }
  else{
    cout << "gnuplot invocado com sucesso!" <<endl;
    cout << "Verifique os gráficos produzidos" << endl;
    }
  
  return 0;
}
