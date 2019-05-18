#include <iostream>
#include "compresion.h"
#include "tipos_datos.h"
#include "funciones_impresion.h"

#define NULO 65535

using namespace std;

#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_ARCHIVO_VACIO "El archivo a tratar está vacío."

//Comprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
estado_t comprimir(diccionario & dic, istream * iss, ostream *oss, ptr_busqueda busqueda)
{
    char S;
	unsigned short P = NULO;
	unsigned short indice = NULO;
	bool estado_f; 

	dic.resetear_diccionario();
	//Para primeros 2 carácteres. El primero lo va a encontrar. El segundo no.
	(*iss).read(&S,sizeof(char));
	if( (*iss).eof() == false ){
	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
			return OK;

		P = (unsigned char)S;
		(*iss).read(&S,sizeof(char));
		if((*iss).eof() == false ){


			//Si viene de entrada estándar y recibo \n corto.
			if( S == '\n' && iss == &cin )
			{
				(*oss).write(reinterpret_cast<char*>(&P),sizeof(unsigned short));
				return OK;
			}
			if (busqueda !=  &diccionario::buscar_simbolo_arbol)
				dic.agregar_simbolo(P, S);
			else
				(dic.*busqueda)(P, S); /*si es arbol, agrego en busqueda*/
			(*oss).write(reinterpret_cast<char*>(&P),sizeof(unsigned short));
			P = (unsigned char)S;

		}
		//Si el próximo caracter es EOF lo imprime y sale de la función.
		else
		{
			(*oss).write(reinterpret_cast<char*>(&P),sizeof(unsigned short)); 
			return OK;
		}
		
	}
	//Archivo de entrada vacío.
	else
	{
		cout << MSJ_ARCHIVO_VACIO << endl;
		return OK;
	}

	//Desde el tercer caracter hasta el final.	
	(*iss).read(&S,sizeof(char));
	while( (*iss).eof() == false )
	{	
		//cout << endl << "leo caracter:" << (short)((unsigned char)S) << endl; 
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
		{
			(*oss).write(reinterpret_cast<char*>(&P),sizeof(unsigned short));
			return OK;
		}
		indice = (dic.*busqueda)(P, S);
		if( indice == NULO )
		{	

			// Si se elige el método de árbol, se agrega el simbolo en la busqueda.
			if (busqueda !=  &diccionario::buscar_simbolo_arbol)
				dic.agregar_simbolo(P, S);
			(*oss).write(reinterpret_cast<char*>(&P),sizeof(unsigned short));
			indice = (unsigned char)S;
		}

		P = indice;
		(*iss).read(&S,sizeof(char));
	}
	(*oss).write(reinterpret_cast<char*>(&P),sizeof(unsigned short));
	return OK;
}

//Descomprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
estado_t descomprimir(diccionario & dic, istream * iss, ostream *oss)
{  
	char S;
	unsigned short aux_u;
	bool Pr_carac_flag = false;     
	unsigned short indice_anterior=0, indice_actual = 0;

	// Para primer caracter
	(*iss).read(reinterpret_cast<char*>(&indice_actual),sizeof(unsigned short));
	if ( (*iss).eof() == true )
	{
		if( Pr_carac_flag == false )
		{
			cout << MSJ_ARCHIVO_VACIO << endl;
			return OK;
		}
	}

	Pr_carac_flag = true;

	S = dic.obtener_S(indice_actual);
	(*oss).write(&S,sizeof(S));

	//Si viene de entrada estándar y recibo \n corto.
	if(indice_actual == '\n'  && iss == &cin)
		return OK;

	//Del segundo caracter hasta el final.

	indice_anterior = indice_actual;

	(*iss).read(reinterpret_cast<char*>(&indice_actual),sizeof(unsigned short));

    while ( (*iss).eof() == false )        
    {

	//Uso la posición de indice_actual para saber si esta o no en el diccionario
        if(indice_actual <= dic.obtener_ult_())
		{
		   	//ubic = indice_actual;                                    
            dic.imprimir_indice(indice_actual, oss);
            aux_u = dic.obtener_indice(indice_actual);            
			dic.agregar_simbolo(indice_anterior,aux_u);
		}
        else
        {
            aux_u = dic.obtener_indice(indice_anterior);  
			dic.agregar_simbolo(indice_anterior,aux_u);
            dic.imprimir_indice(dic.obtener_ult_(), oss);
        }

		//Si viene de entrada estándar y recibo \n corto.
		if( indice_actual == '\n' && iss == &cin )
			return OK;

	indice_anterior = indice_actual;
	
	(*iss).read(reinterpret_cast<char*>(&indice_actual),sizeof(unsigned short));
	
    }

    return OK;
}
