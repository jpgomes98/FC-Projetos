---|Projeto 4|--------------------------------------------------------------

João Pedro Gomes ist187327
Mariana Silva    ist187336

16 de dezembro de 2016
----------------------------------------------------------------------------

---|Questão 1|---------------------------------------------------------------
Hamiltoniano
H=(h^2)/m*k+ V(x)

em que k=-(1)/(2)*(d^2)/(dx^2)

Então da equação de Schrodinger, 

(h^2)/(2*m)*((d^2)phi)/(dx^2)+(k)/(2)*x^2*phi=Ephi

obtemos a equação matricial aos valores próprios se estivermos num sistema de unidades em que h=m=1,

H*phi=E*phi
onde H, como referido antes é H = ((h^2)/m*k) * (d^2)phi)/(dx^2) + V(x).


---|Questão 2|---------------------------------------------------------------
-> Alíneas a e b
Já tínhamos feito o que foi pedido nas alíneas a e b de modo a que temos no código da pasta g2p4c2 os operadores já antes construídos por nós tais como as funções. Comentamos então o código e melhoramos a sua eficiência. 

-> Alínea c
A alínea c encontra-se na pasta g2p4c3.
Aqui calculamos o tempo que demora a inverter matrizes com N_MAX={9,99,999} que resultam da alínea 1.a)

Após fechar todas as janelas do computador exceto as necessárias corremos o código e obtivemos os seguintes resultados:

N_MAX=9   -> 8.9e-05 segundos;
N_MAX=99  -> 0.000987 segundos;
N_MAX=999 -> 1.48635 segundos.

Verficamos então que o aumento de N_MAX tem um papel significativo no aumento do tempo de inversão.

---|Questão 3|---------------------------------------------------------------
->Alínea a
 Recorrendo ao programa criado durante as aulas de laboratório para resolver a equação de Schrödinger num caso em que o potencial é o potencial de um oscilador harmónico, revimos o algoritmo de obtensão do maior vetor próprio.
 Este algoritmo baseia-se no produto sucessivo de vetores, à direita da matriz, a partir de um "guess" inicial aleatório. Os vetores resultantes são de seguida normalizados e faz-se de novo o produto pela matriz, gerando-se assim uma sucessão de vetores que converge para o maior vetor próprio da matriz.
 O critério de paragem corresponde a observar a estabilização de uma das componentes, pela sucessiva redução da diferença entre componentes de vetores sucessivos. O código relativo a esta parte do projeto encontra-se incluído numa classe de matrizes que é utilizada ao longo de todo o exercicio 3 (neste caso sao as funçoes "eigenspace").

->Alínea b
Nesta questão, voltamos a utilizar a classe de matrizes criada nas aulas práticas para termos disponíveis funçoes que efetuam o processo de cálculo anteriormente descrito para calcular o maior vetor proprio e de seguida recorre ao método de Gram-Schmidt para, a partir desse vetor, gerar o vetor próprio seguinte, obrigando-o a ser ortogonal ao anterior e aplicando de novo o método dos produtos pela matriz para gerar uma sucessão convergente para o vetor proprio seguinte. À medida que se aumenta o numero de vetores proprios calculados, vao-se usando esses mesmos vetores para produzir os subsequentes, por ortogonalização daqueles que saem da sucessao de produtos matriciais. Os valores proprios sao obtidos pela multiplicaçao a esquerda e à direita.
Obtivemos os 4 primeiros vetores proprios da matriz H do ex1, porque, mais uma vez, realizamos o exercicio 3 todo junto. As funçoes que geram estes vetores é a "eigenspace" da classe de mtrizes em "Matrix.cpp"
->Alínea c
Por fim, aplicamos à matriz H gerada no ex. 1 os métodos anteriores e ainda a inversão de matrizes, os quais utilizamos para calcular os vetores e valores próprios num sentido diferente, isto é, do menor para o maior. Aplicamos este código à matriz H do ex1, estando o mesmo presente na funçao "solveSchrodinger". Obtendo os 4 primeiros vetores proprios, efetuamos o plot dos mesmos. Os graficos encontram-se numa pasta intitulada "Mathematica" anexada. Produz-se tambem uma compilaçao no gnuplot dos 4 graficos sendo que o script que gera a imagem pode ser alterado em caso de nao funcionar.
->Alínea d
Concluímos, após visualização dos gráficos resultantes da alínea c, que os primeiros 2 vetores próprios representam moléculas ligadas e os 2 restantes representam moléculas livres.

---|NOTA|-------------------------------------------------------------------- 
Para todos os códigos aqui utilizados a compilação encontra-se compactada no Makefile e basta portanto fazer make na command line.
