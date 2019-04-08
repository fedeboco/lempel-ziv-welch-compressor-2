CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: tp0.exe

tp0.exe: main.cc cmdline.cc arreglo.cc compresion.cc compresion.h arreglo.h cmdline.h
	$(CXX) $(CXXFLAGS) -o tp0.exe cmdline.cc main.cc arreglo.cc compresion.cc

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
