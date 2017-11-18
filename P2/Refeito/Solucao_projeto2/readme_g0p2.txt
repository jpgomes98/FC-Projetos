FICHEIROS:

g0p2c0.cpp , para 1.a) e 1.b), o programa le do teclado, para ler dum ficheiro usar o comando de linha ./g0p2c0.cpp < g0p2c0_inputHO.txt
nota: prescindimos de fazer 1.a) pois usamos diretamente funções

folder g0p2c0_infourfiles, para 1.b) partir o código em 4 partes, compilar com a instrução; g++ -o g0p2c0.cpp g0p2c0_main.cpp g0p2c0_RuKuNew1.cpp g0p2c0_Fovm.cpp g0p2c0_header.h
nota: também compila sem o header fazendo apenas; g++ -o g0p2c0.cpp g0p2c0_main.cpp g0p2c0_RuKuNew1.cpp g0p2c0_Fovm.cpp

g0p2c0.nb, para criar os plots do oscilador harmónico para g0p2c0.cpp e o folder g0p2c0_infourfiles, usa g0p2c0_out.txt

g0p2c1.cpp , para 2.c), os dados usados são colocados no ficheiro de input g0p2c1_inputsatelite.txt
nota: prescindimos de fazer 2.a) pois usamos diretamente a força so satélite tri-dimensional

g0p2c2.cpp, para 2.d) onde usámos o código 3Dvector.cpp como exemplo para implementar a estrutura, usa os mesmos dados de input anteriores em g0p2c1_inputsatelite.txt

g0p210.nb, para criar os plots do oscilador harmónico para g0p2c1.cpp g0p2c2.cpp, usa g0p2c1_out.txt


NOTA: 
sendo uma correção mostramos os plots no ficheiro mathematica (para um caso apenas e não para três casos),
na entrega do projeto os grupos devem mostrar os plots fora do ficheiro mathematica para cada um dos três casos.

COMENTÀRIOS:

1.a) Verificámos que o passo considerado é suficiente para o plot, passar de 
n_max=2500 e h =.02 
para 
n_max=5000 eh=.01 
não origina uma alteração visível no plot, mudando o último ponto em cerca de 1 por mil;
e ainda os plots não ocupam muita memória, apenas dezenas de kb, pelo que podemos mostrar todos os pontos.

1.a) A frequência inicial, em todos os três casos é semelhante a w0, a frequência final é semelhante a wf, a final amplitude é máxima quando wf=w0.

1.b) Obtemos o memsos resultado que em 1.a).

2.a) Devemos de novo obter o mesmo que em 1.a) e 1.b), mas nesta resolução saltamos este passo e vamos logo para o satélite.

2.b) Usámos um passo pequeno h=.01 para estabilidade dos resultados (reduzindo o passo para metade o resultado é praticamente o mesmo, mas duplicando o resultado muda)), mas muitos passos n_max=5000000 para dar algumas órbitas; para não criar um ficheiro demasiado grande (ficamos pelas centenas de kb), imprimimos os resultados a cada n_jump=1000 passos pois visualmente o efeito é o mesmo dado que ainda temos uma grande densidade de pontos. 

Para a velocidade levemente superior à velocidade de escape o satélite escapa à terra.
Para a velocidade inermédia o satélite cai na terra após completar 4 órbitas.
Para a velocidade levemente superior à velocidade da órbita circular o satélite cai na terra antes de completar 1 órbita.

2.c) Obtemos o mesmo resultado que em 2.b).



