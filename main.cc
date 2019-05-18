// clase cmdline, cmdline.h y cmdline.cc provistos por cátedra.
// Uso de variables y funciones opt_ basadas en main.cc desarrollado por lesanti (2012/09/15 12:23:57).

//Compresor y descompresor tipo LZW.
//Autores: Chaparro Raúl Antonio, Cuadrado María Sol, Pérez Boco Federico Tomás.
//Fecha: 23/5/2019
//95.12 - Algoritmos y Programación II - FIUBA

#include <compresion.h>
#include <cmdline.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tipos_datos.h"
#include "funciones_impresion.h"

#define MAX_VECTOR 65536

#define MSJ_ERROR_COMP "Compresión fallida."
#define MSJ_OK_COMP "Compresión correcta."
#define MSJ_ERROR_DESCOMP "Descompresión fallida."
#define MSJ_OK_DESCOMP "Descompresión correcta." 
#define MSJ_STD_INPUT "Entrada estándar."
#define MSJ_DEFAULT_OP "Operación no especificada. Comprimiendo por defecto."
#define MSJ_ERROR_OPENING "No se puede abrir "
#define MSJ_ERROR_OPERATION "Invocación inválida."
#define MSJ_COMP_TIME "Tiempo de compresión: "
#define MSJ_DESCOMP_TIME "Tiempo de descompresión: "

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_process(string const &);
static void opt_method(string const &);
static void opt_help(string const &);

// TABLA DE OPCIONES:
// Columna 1: Opción adicional (1) o no (0).
// Columna 2: Nombre corto de opción.
// Columna 3: Nombre largo de opción.
// Columna 4: Valor por defecto a asignar. Si no tiene argumento adicional, no tiene efecto.
// Columna 5: Apunta al método de parseo. Debe retornar void.
// Columna 6: OPT_MANDATORY para que sea obligatoria. OPT_MANDATORY no obligatoria.
// Todos los elementos nulos para indicar final de tabla.

/********************** GLOBAL ***********************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "process", NULL, opt_process, OPT_DEFAULT},
	{1, "m", "method", NULL, opt_method, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

static bool comprimir_archivo = false;
static bool descomprimir_archivo = false;
static ptr_busqueda busqueda =  &diccionario::buscar_simbolo_lineal;;

//static typedef const unsigned short (diccionario::*ptr_busqueda)(const unsigned short &, const char &);
/*****************************************************/

static void opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", entrada estándar.
	// Caso contrario, abre archivo en modo lectura.
	if( arg == "-" )
	{
		iss = &cin; // Entrada estandar cin como flujo de entrada.
		cout << MSJ_STD_INPUT << endl;
	}
	else 
	{
		ifs.open(arg.c_str(), ios::in | ios::binary);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	if( !iss->good() ) 
	{
		cerr << MSJ_ERROR_OPENING
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", entrada estándar.
	// Caso contrario, abre archivo en modo lectura.
	if( arg == "-" )
	{
		oss = &cout; // Salida estandar cout como flujo de salida.
	} 
	else 
	{
		ofs.open(arg.c_str(), ios::out | ios::binary);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	if( !oss->good() )
	{
		cerr << MSJ_ERROR_OPENING
		     << arg
		     << "."
		     << endl;
		exit(1); //EXIT: Termina programa por completo.
	}
}

static void opt_process(string const &arg)
{

	if( arg == "compress" )
	{
		comprimir_archivo = true;
	}
	else if( arg == "decompress" )
	{
		descomprimir_archivo = true;
	}
	else
	{
		cout << MSJ_ERROR_OPERATION << endl;
		cout << "Documentación: ./tp1.exe --help" << endl;
		exit(1);
	}
		

}

static void opt_method(string const &arg)
{
	if( arg == "list" )
		busqueda = &diccionario::buscar_simbolo_lista;
	else if( arg == "normal" )
		busqueda = &diccionario::buscar_simbolo_lineal;
	else if( arg == "tree" )
		busqueda = &diccionario::buscar_simbolo_arbol;
	else
	{
		cout << "Búsqueda normal seleccionada por defecto." << endl;
		busqueda = &diccionario::buscar_simbolo_lineal;
	}
}

static void opt_help(string const &arg)
{
	cout << "\n<<<<COMPRESOR LZW V2>>>> Chapparro, Cuadrado, Pérez Boco.\n\n"
		 << "COMPRIMIR: " 
		 << "./tp1.exe -p compress [-i file] [-o file] \n"
		 << "DESCOMPRIMIR: " 
		 << "./tp1.exe -p decompress [-i file] [-o file] \n\n"
		 << "De no especificarse archivo de entrada o salida, utiliza la línea de comandos.\n"
		 << "De no especificarse una operación, comprime por defecto."
	     << endl << endl;
	exit(0);
}

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto tipo option_t (struct) declarado globalmente.
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline.
	estado_t estado;
	fstream tfs;
	ostream * tiempos_fs;
	tfs.open("tiempos.csv", fstream::app | fstream::out);
	tiempos_fs = &tfs;

	//Descompresión.
	if( descomprimir_archivo && !comprimir_archivo )
	{
		unsigned t0,t1;
		t0=clock();
		diccionario dic(MAX_VECTOR);
		dic.cargar_ASCII();
		if( (estado=descomprimir(dic, iss, oss)) != OK )
		{
			imprimir_error(estado);
			return 1;
		}
		t1 = clock();
		double time (double(t1-t0)/CLOCKS_PER_SEC);
		imprimir_mensaje(MSJ_ESTADO_OK_DESCOMP);
		cout << MSJ_DESCOMP_TIME << time << endl;
		(*tiempos_fs) << time << endl;
	}

	//Compresión.
	else if( !descomprimir_archivo && comprimir_archivo )
	{
		unsigned t0,t1;
		t0=clock();
		diccionario dic(MAX_VECTOR);
		dic.cargar_ASCII();
		if( (estado=comprimir(dic, iss, oss,busqueda))!= OK )
		{
			imprimir_error(estado);
			return 1;
		}
		t1 = clock();
		double time (double(t1-t0)/CLOCKS_PER_SEC);
		imprimir_mensaje(MSJ_ESTADO_OK_COMP);
		cout << MSJ_COMP_TIME << time << endl;
		(*tiempos_fs) << time << ", ";
	}

	//Compresión y descompresión indefinido.
	else if( descomprimir_archivo && comprimir_archivo )
	{
		return 1;
	}

	//Por defecto.
	else
	{
		unsigned t0,t1;
		t0=clock();
		cout << MSJ_DEFAULT_OP << endl;
		diccionario dic(MAX_VECTOR);
		dic.cargar_ASCII();
		if( (estado=comprimir(dic, iss, oss,busqueda))!= OK )
		{
			imprimir_error(estado);
			return 1;
		}
		t1 = clock();
		double time (double(t1-t0)/CLOCKS_PER_SEC);
		imprimir_mensaje(MSJ_ESTADO_OK_COMP);
		(*tiempos_fs) << time << ", ";
		cout << MSJ_COMP_TIME << time << endl;

	}
	ifs.close();
	ofs.close();
	return 0;
}
