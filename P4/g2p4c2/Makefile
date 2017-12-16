all: g2p4c2


g2p4c2: Matrix.o Main.o
		g++  -o g2p4c2 Main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h
		g++ -o Matrix.o -c Matrix.cpp

Main.o: Main.cpp Matrix.h
		g++ -o Main.o -c Main.cpp


clean:
		rm -f g2p4c2 Main.o Matrix.o
