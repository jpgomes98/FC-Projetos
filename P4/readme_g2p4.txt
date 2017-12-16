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

obtemos a equação matricial dos valores próprios se estivermos num sistema de unidades em que h=m=1,

H phi=E phi

onde H, como referido antes é H=(h^2)/m*k+ V(x).


---|Questão 2|---------------------------------------------------------------
-> Alíneas a e b
Já tínhamos feito o que foi pedido nas alíneas a e b de modo a que temos no código da pasta g2p4c2 os operadores já antes construídos por nós tais como as funções. Comentamos então o código e melhoramos a sua eficiência. 

-> Alínea c
A alínea c encontra-se na pasta g2p4c3.
Aqui calculamos o tempo que demora a inverter matrizes com N_MAX={9,99,999} que resultam da alínea 1.a)

Após fechar todas as janelas do computador exceto as necessárias corremos o código e obtivemos os seguintes resultados:

N_MAX=9   -> 5.5e-05 segundos;
N_MAX=99  -> 0.000984 segundos;
N_MAX=999 -> 1.48008 segundos.

Verficamos então que o aumento de N_MAX tem um papel significativo no aumento do tempo de inversão.

---|Questão 3|---------------------------------------------------------------
->Alínea a



->Alínea b

->Alínea c
