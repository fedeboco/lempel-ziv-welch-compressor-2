#include <iostream>
#include "compresion.h"
#include "arreglo.h"
using namespace std;

bool cargarASCII(diccionario & dic)
{
    for(int i=0; i<=255; i++)
		dic.asignar_secuencia(i,-1,char(i));
    return 1;
}

bool comprimir(diccionario & dic, istream * iss, ostream *oss)
{
    char S;
	int buffer_size = 1000000;
	diccionario buffer(buffer_size);

	

	// para que no quede cargada al azar
	dic.resetear_diccionario();

	int P = -1;
	int indice = -1;

	//Para primeros 2 carácteres.
	//El primero lo va a encontrar. El segundo no.
	if( (S = (*iss).get()) != EOF ){

		 // busco primer caracter (encuentra)
		indice = dic.buscar_secuencia(-1, S);
		P = indice;
		if( (S = (*iss).get()) != EOF ){

			 //agrego primer secuencia (no encuentra)
			dic.agregar_secuencia(P, S);
			//imprimo salida
			*oss << P; 
			//busco la posicion de S sin prefijo
			P = dic.buscar_secuencia(-1,S);

		}

	}

	int j = 0;
	while( (S = (*iss).get()) != EOF )
	{	
		indice = dic.buscar_secuencia(P, S); // busco secuencia

		//Si no la encuentro
		if( indice == -1 )
		{
			//la agrego al final
			dic.agregar_secuencia(P, S);
			//agrego a buffer para imprimir
			buffer.asignar_secuencia(j, P, S);
			//busco la posicion de S sin prefijo
			indice = dic.buscar_secuencia(-1,S);

			j++;

		}
		P = indice;

		//vacío buffer
		if( j >= buffer_size )
		{
			//*oss << buffer.obtener_P(i); //imprimo salida (1ero)
			j = 0;
			for(int i = 0; i < buffer_size; i++)
			{
				*oss << "," << buffer.obtener_P(i); //imprimo salida
			}
		}


	}

	buffer.asignar_secuencia(j, P, S);

	//vacío lo que quedó del buffer
	for(int i = 0; i <= j; i++)
	{
		*oss << "," << buffer.obtener_P(i);
	}



    return 1;

}