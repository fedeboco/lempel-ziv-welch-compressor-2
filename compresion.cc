#include <iostream>
#include "compresion.h"

using namespace std;

#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_ARCHIVO_VACIO "El archivo a tratar está vacío."

//Comprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
bool comprimir(diccionario & dic, istream * iss, ostream *oss)
{
    char S;
	int P = -1;
	int indice = -1;

	//Fede: Para primeros 2 carácteres. El primero lo va a encontrar. El segundo no.
	if( (S = (*iss).get()) != EOF ){
	
		P = dic.buscar_secuencia(-1, S);
		if( (S = (*iss).get()) != EOF ){
			dic.agregar_secuencia(P, S);
			*oss << P << ","; 
			P = dic.buscar_secuencia(-1,S);
		}
		// Rulo: Si el próximo caracter está vacío lo imprime y sale de la función.
		else
		{
			*oss << P; 
			return 1;
		}
		
	}
	// Rulo: agrego este else para agarrar el caso que el archivo de entrada este vacío.
	else
	{
		cout << MSJ_ARCHIVO_VACIO << endl;
		return 1;
	}

	//Fede: Desde el tercer caracter hasta el final.	
	while( (S = (*iss).get()) != EOF )
	{	
		indice = dic.buscar_secuencia(P, S);
		if( indice == -1 )
		{
			dic.agregar_secuencia(P, S);
			*oss << P << ",";
			indice = dic.buscar_secuencia(-1,S);
		}
		P = indice;
	}
	*oss << P;
	return 0;
}

//Descomprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
bool descomprimir(diccionario & dic, istream * iss, ostream *oss)
{  
    int ubic = 0, aux_u;
	bool Pr_carac_flag = false;     
    
    char indice_actual_aux;
    int indice_anterior=0, indice_actual = 0;
        
    while( (indice_actual_aux=(*iss).get()) != ',' )
    {		
		if ( indice_actual_aux == EOF )
		{
			if( Pr_carac_flag == false )
			{
				cout << MSJ_ARCHIVO_VACIO << endl;
				return true;
			}
			else
			{
				break;
			}
		}
		Pr_carac_flag = true;
		int aux;
    	aux = int(indice_actual_aux) - 48;
    	indice_actual = indice_actual*10 + aux;
    }
	*oss << dic.obtener_S(indice_actual);
    while ( (*iss).eof() == false )        
    {
        indice_anterior = indice_actual;
        indice_actual=0;
        while( (indice_actual_aux=(*iss).get()) != ',' && (*iss).eof() == false )
        {   
			int aux;                
            aux = int(indice_actual_aux) - 48;
            indice_actual = indice_actual*10 + aux;
        }         
            
        //if(diccionario.buscar_indice(indice_actual, &ubic) == true)
        //Rulo: USo la posición de indice_actual para saber si esta o no en el diccionario
        if(indice_actual <= dic.obtener_ult_())
		{
			
        	ubic = indice_actual;                                    
            dic.imprimir_indice(ubic, oss);
            aux_u = dic.obtener_indice(ubic);            
			dic.agregar_secuencia(indice_anterior,aux_u);
		}
        else
        {
            aux_u = dic.obtener_indice(indice_anterior);  
			dic.agregar_secuencia(indice_anterior,aux_u);
            dic.imprimir_indice(dic.obtener_ult_(), oss);
        }
    }
    return 0;
}