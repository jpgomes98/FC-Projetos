
FLAGS:= -O3

all: main


main: Matrix.o main.o timer.o Makefile
		g++ $(FLAGS) -o main main.o Matrix.o timer.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

main.o: main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o main.o -c main.cpp

timer.o: timer.cpp timer.h Makefile
		g++ $(FLAGS) -o timer.o -c timer.cpp

#make run
#run program
run: main
		./main < in.txt

#clean files
#make clean
clean:
		rm -f main timer.o main.o Matrix.o


cleanall:
		rm -f main timer.o main.o Matrix.o out*.txt
