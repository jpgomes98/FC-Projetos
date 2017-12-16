
all: VecAnyD


VecAnyD: VecAnyD.o VecAnyD_main.o
		g++ -O3 -o VecAnyD VecAnyD_main.o VecAnyD.o

VecAnyD.o: VecAnyD.cpp VecAnyD.h
		g++ -O3 -o VecAnyD.o -c VecAnyD.cpp

VecAnyD_main.o: VecAnyD_main.cpp VecAnyD.h
		g++ -O3 -o VecAnyD_main.o -c VecAnyD_main.cpp

clean:
		rm -f VecAnyD VecAnyD_main.o VecAnyD.o

cleanall:
		rm -f VecAnyD VecAnyD_main.o VecAnyD.o


#make run
#run program
run: VecAnyD
		./VecAnyD < in.txt

