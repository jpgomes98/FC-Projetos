
all: VecAnyD


VecAnyD: VecAnyD.o VecAnyD_main.o
		g++ -o VecAnyD VecAnyD_main.o VecAnyD.o

VecAnyD.o: VecAnyD.cpp VecAnyD.h
		g++ -o VecAnyD.o -c VecAnyD.cpp

VecAnyD_main.o: VecAnyD_main.cpp VecAnyD.h
		g++ -o VecAnyD_main.o -c VecAnyD_main.cpp

clean:
		rm -f VecAnyD VecAnyD_main.o VecAnyD.o

