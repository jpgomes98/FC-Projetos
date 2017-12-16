#Makefile para o problema main

FLAGS:= -O3

#make
all: main

main: main.o timer.o Makefile
		g++ $(FLAGS) -o main main.o timer.o

timer.o: timer.cpp timer.h Makefile
		g++ $(FLAGS) -o timer.o -c timer.cpp


main.o: main.cpp timer.h Makefile
		g++ $(FLAGS) -o main.o -c main.cpp




#make run
#run program
run: main
		./main < in.txt

#clean files
#make clean
clean:
		rm -f main timer.o main.o


cleanall:
		rm -f main timer.o main.o out*.txt
