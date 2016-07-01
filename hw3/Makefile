#makefile for hw3
#usage: make main OR make
       
main: hw3.o        
	g++ -std=c++11 -O3 hw3.o -o main 
hw3.o: hw3.cpp             
	g++ -std=c++11 -O3  hw3.cpp -c
clean:                 
	rm -rf hw3.o
run:
	./main -s
