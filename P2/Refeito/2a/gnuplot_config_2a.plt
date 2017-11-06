
#Inicialização do script

set terminal wxt size 1000,600
set size 1, 1.5
set macros

#Ficheiros disponíveis

FC_2a = "'dados_2a.txt'"

#Estilos e títulos

style1 = "lines lt 4 lw 3 title \"Posicao\""
style2 = "lines lt 3 lw 2 title \"Velocidade\""
#style3 = "lines lt 2 lw 2 title \"\""

#Ranges
range1_2 = "using 1:2"
#range1_3 = "using 1:3"
#range1_4 = "using 1:4"
range1_5 = "using 1:5"


Alabels = "set xlabel 't'; set ylabel 'x'"
Blabels = "set xlabel 't'; set ylabel 'v'"


### Start multiplot (1x2 layout)
set multiplot layout 1,2 rowsfirst
# --- GRAPH x
@Alabels
set label 1 'A' at graph 0.92,0.9 font ',8'
plot @FC_2a @range1_2 with @style1
# --- GRAPH v
@Blabels
set label 1 'B' at graph 0.92,0.9 font ',8'
plot @FC_2a @range1_5 with @style2

unset multiplot
### End multiplot

#plot "dados_2a.txt" @range1 with @style1

#pause -1
pause mouse button3,keypress
