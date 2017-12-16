
FLAGS:= -O3

all: g2p4c3


g2p4c3: Matrix.o g2p4c3_main.o Makefile
		g++ $(FLAGS) -o g2p4c3 g2p4c3_main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

g2p4c3_main.o: g2p4c3_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o g2p4c3_main.o -c g2p4c3_main.cpp 


#make run
#run program
run: g2p4c3
		./g2p4c3

#clean files
#make clean
clean:
		rm -f g2p4c3_main.o Matrix.o


cleanall:
		rm -f g2p4c3 *.o

cleandats:
		rm -f schrodinger_*.dat
