// Prueba de la clase cmdline: dado un factor entero pasado por la
// l�nea de comando, leemos una secuencia de n�meros que ingresan
// por la entrada est�ndar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

#include <fstream>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include <cmdline.h>
#include <compresion.h>

#define MAX_VECTOR 65536

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_compress(string const &);
static void opt_decompress(string const &);
static void opt_help(string const &);

// Tabla de opciones de l�nea de comando. El formato de la tabla
// consta de un elemento por cada opci�n a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opci�n lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opci�n.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opci�n en caso que no est� expl�citamente presente
//   en la l�nea de comandos del programa. Si la opci�n no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al m�todo de parseo de la opci�n,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La �ltima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opci�n: cuando la
//   opci�n es obligatoria, deber� activarse OPT_MANDATORY.
//
// Adem�s, la �ltima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "c", "compress", NULL, opt_compress, OPT_DEFAULT},
	{0, "d", "decompress", NULL, opt_decompress, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static bool comprimir_archivo = false;
static bool descomprimir_archivo = false;

/*****************************************************/

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}

static void
opt_compress(string const &arg)
{

	if( descomprimir_archivo )
	{
		cout << "Error: realice una operación a la vez.";
		exit(1);
	}
	comprimir_archivo = true;

}

static void
opt_decompress(string const &arg)
{

	if( comprimir_archivo )
	{
		cout << "Error: realice una operación a la vez.";
		exit(1);
	}
	descomprimir_archivo = true;

}

static void
opt_help(string const &arg)
{
	cout << "cmdline -f factor [-i file] [-o file]"
	     << endl;
	exit(0);
}

int
main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver l�nea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
	
	if( comprimir_archivo ){
		diccionario dic(MAX_VECTOR);
		//cargarASCII(dic);
		dic.cargar_ASCII();
		comprimir(dic, iss, oss);
		cout << "Compresión correcta." << endl;
	}

	if( descomprimir_archivo ){
		diccionario dic(MAX_VECTOR);
		//cargarASCII(dic);
		dic.cargar_ASCII();
		descomprimir(dic, iss, oss);
		cout << "Descompresión correcta." << endl;
	}
	ifs.close();
	ofs.close();
}
