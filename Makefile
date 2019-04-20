CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: tp0.exe

tp0.exe: main.cc cmdline.cc diccionario.cc arreglo.cc secuencia.cc compresion.cc compresion.h  diccionario.h arreglo.h secuencia.h cmdline.h 
	$(CXX) $(CXXFLAGS) -o tp0.exe cmdline.cc main.cc diccionario.cc arreglo.cc secuencia.cc compresion.cc 

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err

valgrind: 
	valgrind ./tp0.exe -c -i "entrada4.txt" -o "salida4.txt"
