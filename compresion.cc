#include <iostream>
#include "compresion.h"
#include "arreglo.h"
using namespace std;

bool cargarASCII(arreglo & dic)
{
    for(int i=0; i<=255; i++)
		dic.asignar_secuencia(i,-1,char(i));
    return 1;
}

bool comprimir(arreglo & dic, istream * iss, ostream *oss)
{
    char S;

	// para que no quede cargada al azar
	dic.resetear_diccionario();

	int P = -1;
	int indice = -1;

	//Para el primer carácter.
	if( *iss >> S ){
		indice = dic.buscar_secuencia(P, S); // busco secuencia
		P = indice;
		*oss << P; //imprimo salida	
	}

	while( *iss >> S )
	{	
		*oss << ",";
		indice = dic.buscar_secuencia(P, S); // busco secuencia

		//Si no la encuentro
		if( indice == -1 )
		{
			//la agrego al final
			dic.agregar_secuencia(P, S);
			//busco la posicion de S sin prefijo
			indice = dic.buscar_secuencia(-1,S);

		}
		P = indice;
		*oss << P; //imprimo salida	
			
	}

    return 1;

}