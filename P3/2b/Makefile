
FLAGS:= -O3

all: VecAnyD


VecAnyD: VecAnyD.o main.o
		g++ $(FLAGS) -o VecAnyD main.o VecAnyD.o

VecAnyD.o: VecAnyD.cpp VecAnyD.h
		g++ $(FLAGS) -o VecAnyD.o -c VecAnyD.cpp

main.o: main.cpp VecAnyD.h
		g++ $(FLAGS) -o main.o -c main.cpp


#make run
#run program
run: VecAnyD
		./VecAnyD < in.txt

#clean files
#make clean
clean:
		rm -f VecAnyD main.o VecAnyD.o


cleanall:
		rm -f VecAnyD main.o VecAnyD.o out*.txt
