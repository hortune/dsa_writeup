#makefile for hw2
#usage: make main OR make
       
main: hw2.o        
	g++ -std=c++11 -O3 hw2.o -o main 
hw2.o: hw2.cpp             
	g++ -std=c++11 -O3  hw2.cpp -c
clean:                 
	rm -rf hw2.o
run:
	./main -s
