descompresion.exe: descompresion.cpp arreglo.o
		
		g++ -ansi -pedantic -Wall -o descompresion.exe descompresion.cpp arreglo.o

arreglo.o: arreglo.h arreglo.cpp
		
		 g++  -g -Wall -c arreglo.cpp 

.PHONY: clean
clean:
		rm -rf *.o



