
#Inicialização do script

set terminal wxt size 1000,600
set size 1, 1.5
set macros

#Ficheiros disponíveis

FC_2a = "'dados_2a.txt'"
FC_2b = "'dados_2b.txt'"

#Estilos e títulos

style1 = "lines lt 4 lw 3 title \"Satelite-Terra\""
style2 = "lines lt 3 lw 2 title \"Velocidade\""
style3 = "lines lt 2 lw 2 title \"Trajetoria\""

#Ranges
range2_6 = "using 2:6"
range2_10 = "using 2:10"
#range1_4 = "using 1:4"
range3_4 = "using 3:4"


Alabels = "set xlabel 't'; set ylabel 'd'"
Blabels = "set xlabel 't'; set ylabel '|v|'"
Clabels = "set xlabel 'x'; set ylabel 'y'"


### Start multiplot (1x2 layout)
set multiplot layout 1,3 rowsfirst
# --- GRAPH ro
@Alabels
set label 1 'A' at graph 0.92,0.9 font ',8'
plot @FC_2b @range2_6 with @style1
# --- GRAPH v
@Blabels
set label 1 'B' at graph 0.92,0.9 font ',8'
plot @FC_2b @range2_10 with @style2
# --- GRAPH traj
@Clabels
set label 1 'C' at graph 0.92,0.9 font ',8'
plot @FC_2b @range3_4 with @style3

unset multiplot
### End multiplot

#plot "dados_2a.txt" @range1 with @style1

#pause -1
pause mouse button3,keypress
