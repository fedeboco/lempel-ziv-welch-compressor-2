#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "arreglo.h"
using namespace std;
#define MAX_VECTOR 65534

#define MSJ_ERROR_FOPEN "No se udo abrir el archivo."
#define MSJ_DIC_LLENO "Se lleno el diccionario, se procede a resetearlo"

int main (){
    
    
    arreglo diccionario(MAX_VECTOR);
    int cont=255;
    int ubic = 0, aux_u;
    //Rulo: Declaro variable para abrrir archivo comprimido.
    ifstream archivo_com; 
    
    archivo_com.open("prueba.csv",ios::binary);

    //Rulo: Armo el diccionario
    for (int i=0;i < 255;i++)    
            diccionario.asignar_secuencia(i,-1,i);           
    
    if(archivo_com.is_open()){
        char indice_actual_aux;
        int indice_anterior=0,indice_actual = 0,aux;
        
        while((indice_actual_aux=archivo_com.get()) != ',')
        {
            aux = int(indice_actual_aux)-48;
            indice_actual = indice_actual * 10+ aux;
        }
        cout << "Primer Indice: " << indice_actual << " Corresponde a:" << diccionario.obtener_S(indice_actual) << endl;
       
        while (archivo_com.eof() == false)        
        {
            indice_anterior = indice_actual;
            indice_actual=0;
             while((indice_actual_aux=archivo_com.get()) != ',' && archivo_com.eof() == false)
            {                   
                aux = int(indice_actual_aux)-48;
                indice_actual = indice_actual * 10+ aux;
            }         
            
            //if(diccionario.buscar_indice(indice_actual, &ubic) == true)
            //Rulo: USo la posición de indice_actual para saber si esta o no en el diccionario
            if (indice_actual <= cont) 
            {   
                
                ubic = indice_actual;                                    
                diccionario.imprimir_indice(ubic);
                aux_u = diccionario.obtener_indice(ubic);            
               if((diccionario.agregar_secuencia(indice_anterior,aux_u,&cont))==false) //Se rompia aca
                {
                    cout << MSJ_DIC_LLENO << endl;
                }

            }
            else
            {
                aux_u = diccionario.obtener_indice(indice_anterior);  
                if((diccionario.agregar_secuencia(indice_anterior,aux_u,&cont))==false) 
                {
                    cout << MSJ_DIC_LLENO << endl;
                }
                diccionario.imprimir_indice(cont);
            }
        }
        
    }
    else
    {
            cout << MSJ_ERROR_FOPEN;
    }
    
    return 0;
    }