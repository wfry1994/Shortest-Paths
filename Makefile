.PHONY : run clean

run: main
	./main
main: main.o
	g++ -g -std=c++11 -o main main.o
main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp
clean:
	rm *.o main
