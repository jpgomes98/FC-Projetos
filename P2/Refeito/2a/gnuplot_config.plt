#
# lt: 1 - vermelho        2 - verde        3 - azul              4 - violeta   
#     5 - azul claro      6 - castanho     7 - amarelo torrado   8 - laranja
#
# lw: 1 - fixo            2 - medio        3 - largo        .....
#

set term x11 
set macros
style1 = "lines lt 4 lw 3 title \"Oscilador a 3dim\""
#style2 = "lines lt 3 lw 2 title \"Metodo de Runge-Kutta 2\""
#style3 = "lines lt 2 lw 2 title \"Funcao Exponencial\""
range1 = "using 1:2"
#range2 = "using 1:3"
#range3 = "using 1:4"

### Start multiplot (2x2 layout)
set multiplot layout 2,2 rowsfirst
# --- GRAPH a
set label 1 'a' at graph 0.92,0.9 font ',8'
plot f(x) with lines ls 1
# --- GRAPH b
set label 1 'b' at graph 0.92,0.9 font ',8'
plot g(x) with lines ls 1
# --- GRAPH c
set label 1 'c' at graph 0.92,0.9 font ',8'
plot h(x) with lines ls 1
# --- GRAPH d
set label 1 'd' at graph 0.92,0.9 font ',8'
plot k(x) with lines ls 1
unset multiplot
### End multiplot

plot "dados_2a" @range1 with @style1

#"Prog33_02__Data.txt" @range2 with @style2, "Prog33_02__Data.txt" @range3 with @style3

#pause -1
pause mouse button3,keypress
