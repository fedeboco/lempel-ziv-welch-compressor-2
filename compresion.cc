#include <iostream>
#include "compresion.h"
#include "arreglo.h"
using namespace std;

#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_DIC_LLENO "Se lleno el diccionario, se procede a resetearlo"

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

bool descomprimir(diccionario & dic, istream * iss, ostream *oss)
{  
    
    int cont=255;
    int ubic = 0, aux_u;
    
    //Rulo: Armo el diccionario
    //for (int i=0;i < 255;i++)    
    //        dic.asignar_secuencia(i,-1,i);           
    
    if( /*(*iss).is_open()*/ 1 == 1){
        char indice_actual_aux;
        int indice_anterior=0,indice_actual = 0,aux;
        
        while((indice_actual_aux=(*iss).get()) != ',')
        {
            aux = int(indice_actual_aux)-48;
            indice_actual = indice_actual * 10+ aux;
        }
        *oss << "Primer Indice: " << indice_actual << " Corresponde a:" << dic.obtener_S(indice_actual) << endl;
       
        while ((*iss).eof() == false)        
        {
            indice_anterior = indice_actual;
            indice_actual=0;
             while((indice_actual_aux=(*iss).get()) != ',' && (*iss).eof() == false)
            {                   
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
               if((dic.agregar_secuencia(indice_anterior,aux_u,&cont))==false) //Se rompia aca
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
        
    }
    else
    {
            cout << MSJ_ERROR_FOPEN;
    }
    
	return 1;
}