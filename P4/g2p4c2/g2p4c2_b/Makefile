FLAGS:= -O3

all: g2p4c2_b


g2p4c2_b: Matrix.o Main.o Makefile
		g++ $(FLAGS) -o g2p4c2_b Main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

Main.o: Main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Main.o -c Main.cpp


#make run
#run program
run: g2p4c2_b
		./g2p4c2_b 

#clean files
#make clean
clean: g2p4c2_b
		rm -f Main.o Matrix.o


cleanall:
		rm -f g2p4c2_b *.o
