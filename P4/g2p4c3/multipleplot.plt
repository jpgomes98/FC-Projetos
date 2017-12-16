
# FC / Projeto 4 / Gnuplot configuração

set terminal png size 1920,1080
set output '4funcoes_onda.png'
set print "-"
set macros

print "Inicializando o gnuplot..."

set xrange [-100:100]
set yrange [-0.3:0.3]
set format y "%.2f"
set key box opaque

#Estilos e títulos

style1 = "points lt 6 lw 0.5 title \"n = 0\""
style2 = "points lt 1 lw 0.5 title \"n = 1\""
style3 = "points lt 4 lw 0.5 title \"n = 2\""
style4 = "points lt 7 lw 0.5 title \"n = 3\""

Alabels = "set xlabel 'x'; set ylabel '{/Symbol f}'"

filename = ""
myFile =  'schrodinger_999.dat' 
#system(ls schrodinger_*.dat)
#print filename

# Margens 

if (!exists("MP_LEFT"))   MP_LEFT = .1
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_GAP"))    MP_GAP = 0.05

print "A preparar impressão..."
### Start multiplot (2x2 layout)

set multiplot layout 2, 2 columnsfirst title "{/:Bold=15 Equação de Schrodinger - 4 Estados}" \
  margins screen MP_LEFT, MP_RIGHT, MP_BOTTOM, MP_TOP spacing screen MP_GAP

# --- n = 0
@Alabels
plot myFile u 1:2 w @style1,
# --- n = 1
@Alabels
set xrange [-100:100]
set yrange [-0.15:0.15]
set format y "%.2f"
plot myFile u 1:3 w @style2,
# --- n = 2
@Alabels
set xrange [-100:100]
set yrange [-0.1:0.1]
set format y "%.2f"
plot myFile u 1:4 w @style3,
# --- n = 3
@Alabels
set xrange [-100:100]
set yrange [-0.1:0.1]
set format y "%.2f"
plot myFile u 1:5 w @style4,

unset multiplot
### End multiplot


print "A gerar ficheiro .png..."
replot
set output
print "Sucesso! Procure o ficheiro '4funcoes_onda.png'."

pause 1

