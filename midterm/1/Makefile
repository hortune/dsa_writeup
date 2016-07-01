#makefile for 2
#usage: make main OR make
       
main: main.o        
	g++ -std=c++11 -O3 main.o -o main 
hw3.o: main.cpp             
	g++ -std=c++11 -O3  main.cpp -c
clean:                 
	rm -rf hw3.o
run:
	./main -s
