#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#define GNUPLOT "gnuplot "

using namespace std;


class Calor{
  
  /* Tamanho do espaço gerado - 2D */
  int npos;
public:
  double x, y;
  double hx;
  double t;
  double ht;
  double **tt0, **tt1;
  explicit Calor(int n); // construtor
  ~Calor(); // destrutor

  /* Métodos */
  
  void setup(double Tx_a1, double Tx_a2, double Ty_b1, double Ty_b2, double T_int);
  int size() const;
  void print(ofstream& out, int check);
  void setStep(double h_esp, double h_temp)
  {
    hx = h_esp;
    ht = h_temp;
  };

  /* Funções de resolução da Eq. Diferencial Parcial */
  
  double evolucao_2d(double T_xy, double T_x0, double T_x2, double T_y0, double T_y2, double k);

};

Calor::Calor(int n): npos(n)
{
  t = 0;
  
  tt0 = new double*[npos];
  tt1 = new double*[npos];
  
  for (int i = 0; i < npos; i++)
    {
      tt0[i] = new double[npos];
      tt1[i] = new double[npos];
    }

}

Calor::~Calor()
{
  for (int i = 0; i < npos; i++)
    {
      delete[] tt0[i];
      delete[] tt1[i];
    }
  
  delete[] tt0;
  delete[] tt1;
  
  cout << "Os objetos da classe foram eliminados com sucesso" << endl;
}

void Calor::setup(double Tx_a1, double Tx_a2, double Ty_b1, double Ty_b2, double T_int)
{
  int j = 1, i = 1;
  
  /* Potencial na fronteira */
  
  /* Ao longo de x */

  for (int v = 0; v < npos; v++)
    {
      tt0[v][0] = Ty_b1;
      tt0[v][npos - 1] = Ty_b2;
      tt1[v][0] = Ty_b1;
      tt1[v][npos - 1] = Ty_b2;
    }

  /* Ao longo de y, sem incluir as posições extremas */

  for (int v = 0; v < npos; v++)
    {
      tt0[0][v] = Tx_a1;
      tt0[npos - 1][v] = Tx_a2;
      tt1[0][v] = Tx_a1;
      tt1[npos - 1][v] = Tx_a2;
    }
  
  /* Inicialização das configurações */
  
  for (i = 1; i < (npos - 1); i++)
    {
      for (j = 1; j < (npos - 1); j++)
	{
	  tt0[i][j] = T_int;
	  tt1[i][j] = T_int;
	}
      j = 1;
    }
}

int Calor::size() const
{
  return npos;
}

void Calor::print(ofstream& out, int check)
{
   /* Obtenção dos dados após algumas iteradas - a cada 30s e também após 150s */   
  for (int k = 0; k < npos; k++)
    {
      for (int w = 0; w < npos; w++)
	{
	  if (check == 1) /* Controlar quando imprime para o ficheiro dos 30s e dos 150s */
	    {
	      cout << t << " " << k * hx << " " << w * hx << " " << tt0[k][w] << endl;
	      out << k * hx << " " << w * hx << " " << tt0[k][w] << endl;
	    }
	  else if(check == 0) /* Imprimir para um ficheiro de 30s em 30s - Impressão Geral*/
	    {
	      out << t << " " << k * hx << " " << w * hx << " " << tt0[k][w] << endl;
	    }
	}
    }
}

/* Método Numérico */

double Calor::evolucao_2d(double T_xy, double T_x0, double T_x2, double T_y0, double T_y2, double k)
{ 
  double T1 = 0;
  
  T1 = T_xy + ((ht * k)/(hx * hx)) * (T_x0 + T_x2 + T_y0 + T_y2 - 4 * T_xy);
  
  return T1;
}


int main ()
{
  /* Definir as fronteiras */
  double Tx_a1, Tx_a2, Ty_b1, Ty_b2; //Temperaturas nas fronteiras da placa
  /****************/
  double hx, ht; // Passos no tempo e no espaço
  int npos; // Número de pontos por cada lado do quadrado
  /***************/
  
  int i = 1, j = 1; // Posição atual na matriz de pontos no espaço 2D
  int n_30 = 1;
  int n_150 = 1;
  
  /* Variável para controlar o número de vezes que passam 30s */
  int check = 0;
  /****************/
  /* Variáveis para estudar quanto tempo é necessário para o centro da placa ter uma temperatura que apenas difere em 1% em relação à temperatura da fronteiro (ie, do forno) */
  double dif = 0;
  int check_dif = 0;
  /****************/
  
  /* Parâmetros iniciais recebidos no ficheiro de leitura */
  double t_max;
  double k, L;
  double T_front;
  double T_int;
  int n_max, n_print;
  
  /* Ficheiro de leitura dos parâmetros */
  ifstream input ("parametros_sistema.txt");

  /* Ficheiro de output geral */
  ofstream output ("Eq_Calor_2d.dat");

  /* Ficheiros para imprimir ao fim dos 30s e dos 1m90s = 150s */
  ofstream output30s ("Temperatura_30s.dat");
  ofstream output1m90s ("Temperatura_150s.dat");

  if (input.is_open())
    {
      input >> k;
      input >> L;
      input >> T_front;
      input >> T_int;
      input >> hx;
      input >> ht;
      input >> n_max;
      input >> n_print;
    }

  npos = (int) ((double) L) / ((double) hx);
  cout << npos << endl;

  Calor Placa(npos); /* Instanciar um objeto da classe */
  Placa.setStep(hx, ht);

  /* Estabelecer as condições fronteira */
  Tx_a1 = T_front;
  Tx_a2 = T_front;
  Ty_b1 = T_front;
  Ty_b2 = T_front;

  Placa.setup(Tx_a1, Tx_a2, Ty_b1, Ty_b2, T_int);

  for(int z = 1; z <= n_max; z++)
    {
      for (i = 1; i < (Placa.size() - 1); i++)
	{
	  for (j = 1; j < (Placa.size() - 1); j++) 
	    {
	      Placa.tt1[i][j] = Placa.evolucao_2d(Placa.tt0[i][j], Placa.tt0[i-1][j], Placa.tt0[i+1][j], Placa.tt0[i][j-1], Placa.tt0[i][j+1], k); // calcular a nova distirbuição de temperaturas
	      Placa.tt0[i][j] = Placa.tt1[i][j];
	    }
	}
      
      i = 1;
      j = 1;
      Placa.t += Placa.ht; /* Incremento do tempo */
      if(z % n_print == 0)
	{
	  Placa.print(output, 0); // Impressão Geral para um ficheiro a cada 30s
	}
      if((fmod(Placa.t, 30.) <= 1e-7) && (n_30 == 1)) /* Condição para imprimir após 30s */
	{
	  n_30 = 0; // Só utilizar o tempo correspondente ao primeiro múltiplo de 30 s
	  check = 1;
	  Placa.print(output30s, check);
	  check = 0;
	}
      else if(fmod(Placa.t, 150.) <= 1e-7 && (n_150 == 1)) /* Condição para imprimir após 1m90s */
	{
	  n_150 = 0; // Só utilizar o tempo correspondente ao primeiro múltiplo de 150 s
	  check = 1; 
	  Placa.print(output1m90s, check);
	  check = 0;
	}
      if (((T_front - Placa.tt1[(size_t)(Placa.size()/2)][(size_t)(Placa.size()/2)]) / T_front <= 0.01) && (check_dif == 0))
	{
	  // Verificar quando a temperatura no centro da placa difere apenas da T_fronteira em 1%
	  dif = Placa.t;
	  check_dif = 1;
	}
      /*** DEBUGGING ***/
      /* cout << (T_front - Placa.tt1[(size_t)(Placa.size()/2)][(size_t)(Placa.size()/2)]) << endl;*/
    }
  
  if (dif == 0)
    {
      cout << "O número de passos temporais introduzido pelo utilizador não foi suficiente para a temperatura no centro aumentar o suficiente... Introduza outro valor para o  7º parâmetro. " << endl;
    }
  else
    {
      cout << "Após " << dif << "s, a temperatura do centro da placa difere em 1% apenas da temperatura da fronteira" << endl;
    }

  /* Fechar os streams abertos */
  output.close();
  output30s.close();
  output1m90s.close();

  
  return 0;
}
