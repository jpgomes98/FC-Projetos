
FLAGS:= -O3

all: g2p4c1


g2p4c1: Matrix.o g2p4c1_main.o Makefile
		g++ $(FLAGS) -o g2p4c1 g2p4c1_main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

g2p4c1_main.o: g2p4c1_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o g2p4c1_main.o -c g2p4c1_main.cpp 


#make run
#run program
run: g2p4c1
		./g2p4c1

#clean files
#make clean
clean:
		rm -f g2p4c1_main.o Matrix.o


cleanall:
		rm -f g2p4c1 *.o

cleandats:
		rm -f schrodinger_*.dat
