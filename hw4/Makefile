#makefile for hw4
#usage: make main OR make
       
main: main.o        
	g++ -std=c++11 -O3 main.o -o main 
main.o: main.cpp             
	g++ -std=c++11 -c -O3  main.cpp
clean:                 
	rm -rf main.o
run:
	./main -s
