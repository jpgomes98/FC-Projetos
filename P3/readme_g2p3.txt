
1.a.
Expressão de cada iterada para resolução numérica da Eq. do Calor.

tt1[i][j] = htK/(hxx*hxx) * (tt0[i+1][j] + tt0[i-1][j] + tt0[i][j+1] + tt0[i][j-1] - 4tt0[i][j]) + tt0[i][j]

É semelhante ao passo que foi utilizado na aula para calcular o potencial do campo pela equação de Poisson, no sentido em que utiliza o valor da temperatura no espaço vizinho ao ponto em que será calculada a nova temperatura, mas ao mesmo tempo, difere desta uma vez que corresponde a um método explicito, no qual, ao valor da temperatura na vzinhança, se adiciona o valor da temperatura no instante de tempo anterior, sendo, por isso, uma combinação do método de Euler para resolução de equações diferenciais ordinárias dependentes do tempo e do método da diferença finita para a segunda derivada das variáveis do espaço. 
Neste caso, a dependência do tempo neste método significa que cada iteração (no tempo) tem significado físico, uma vez que calcula uma nova configuração das temperaturas do sistema que representa realmente um estado termodinâmico do sistema. No caso de Poisson, apenas efetuavamos iterações para atualizar o campo de potenciais, sendo que os passos intermédios não representavam nada, na medida em que o potencial é instantâneamente atualizado, aproximadamente.

1b. É necessário que os parâmetros iniciais sejam lidos do ficheiro "parametros_iniciais.txt". A ordem dos parâmetros é a indicada aqui:

1) k
2) Lx = Ly = L
3) T_front
4) T_int
5) ht
6) hx = hy
7) n_max
8) n_print (calculada como sendo 3000 para garantir a impressão dos valores a cada 30s)

1.c. Foi calculado que após 141,23s a diferença entre a temperatura no centro e a temperatura inicialmente definida para a fronteira era inferior a 1%. Tal ilustra o processo físico que acompanha a difusão térmica dependente da condutividade térmica do material em questão. Espera-se que uma condutividade térmica maior venha acompanhada de um menor tempo necessário até esta diferença ser menor do 1%.
