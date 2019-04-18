#include <iostream>
#include "compresion.h"

using namespace std;

#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_DIC_LLENO "Se lleno el diccionario, se procede a resetearlo"
#define MSJ_ARCHIVO_VACIO "El archivo a tratar está vacío"

//Comprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
bool comprimir(diccionario & dic, istream * iss, ostream *oss, const int buffer_size)
{
    char S;
	diccionario buffer(buffer_size);

	int P = -1;
	int indice = -1;

	//Fede: Para primeros 2 carácteres. El primero lo va a encontrar. El segundo no.
	if( (S = (*iss).get()) != EOF ){
	
		indice = dic.buscar_secuencia(-1, S);
		P = indice;
		if( (S = (*iss).get()) != EOF ){
			dic.agregar_secuencia(P, S);
			*oss << P; 
			P = dic.buscar_secuencia(-1,S);
		}
		// Rulo: Si el próximo caracter está vacío lo imprime y sale de la función.
		else
		{
			dic.agregar_secuencia(P, S);
			*oss << P; 
			P = dic.buscar_secuencia(-1,S);
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
	int j = 0;
	while( (S = (*iss).get()) != EOF )
	{	
		indice = dic.buscar_secuencia(P, S);
		if( indice == -1 )
		{
			dic.agregar_secuencia(P, S);
			buffer.asignar_secuencia(j, P, S);
			indice = dic.buscar_secuencia(-1,S);
			j++;
		}
		P = indice;

		//Fede: Vacío buffer.
		if( j >= buffer_size )
		{			
			j = 0;
			for(int i = 0; i < buffer_size; i++)
				*oss << "," << buffer.obtener_P(i); //imprimo salida
		}
	}

	//Fede: Vacío lo que quedó del buffer
	buffer.asignar_secuencia(j, P, S);
	for(int i = 0; i <= j; i++)
		*oss << "," << buffer.obtener_P(i);
	
    return 1;
}

//Descomprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
bool descomprimir(diccionario & dic, istream * iss, ostream *oss)
{  
    
    int cont=255;
    int ubic = 0, aux_u;
	bool Pr_carac_flag = false;
    bool unico_char_flag = false;       
    
    char indice_actual_aux;
    int indice_anterior=0,indice_actual = 0;
        
    while((indice_actual_aux=(*iss).get()) != ',' && unico_char_flag != true)
    {		
		if (indice_actual_aux == EOF )
		{
			if(Pr_carac_flag == false)
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
    	aux = int(indice_actual_aux)-48;
    	indice_actual = indice_actual * 10+ aux;
    }
	*oss << dic.obtener_S(indice_actual);
    while ((*iss).eof() == false)        
    {
        indice_anterior = indice_actual;
        indice_actual=0;
        while((indice_actual_aux=(*iss).get()) != ',' && (*iss).eof() == false)
        {   
			int aux;                
            aux = int(indice_actual_aux)-48;
            indice_actual = indice_actual * 10+ aux;
        }         
            
        //if(diccionario.buscar_indice(indice_actual, &ubic) == true)
        //Rulo: USo la posición de indice_actual para saber si esta o no en el diccionario
        if (indice_actual <= cont) 
        {
        	ubic = indice_actual;                                    
            dic.imprimir_indice(ubic, oss);
            aux_u = dic.obtener_indice(ubic);            
            if((dic.agregar_secuencia(indice_anterior,aux_u,&cont))==false) 
            {
                cout << MSJ_DIC_LLENO << endl;
            }
		}
        else
        {
            aux_u = dic.obtener_indice(indice_anterior);  
            if((dic.agregar_secuencia(indice_anterior,aux_u,&cont))==false) 
            {
                cout << MSJ_DIC_LLENO << endl;
            }
            dic.imprimir_indice(cont, oss);
        }
    }
    return 0;
}