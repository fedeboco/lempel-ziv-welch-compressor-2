#include <iostream>
#include "arreglo.h"
#include "simbolo.h"

using namespace std;

#define ERROR_SIZE_1 "Error: acceso inválido a posición "
#define ERROR_SIZE_2 " en arreglo de tamaño " 
#define ERROR_SIZE_CONSTRUCTOR "Tamaño inválido. No se pudo crear el arreglo."

arreglo::arreglo(const int & size)
{
    if( size > 0 )
    {
        dato_ = new simbolo[size];
        size_ = size;
    }
    else
        cout << ERROR_SIZE_CONSTRUCTOR << endl;

}

arreglo::~arreglo()
{
    if( dato_ )
        delete[] dato_;
}

simbolo & arreglo::operator[](const unsigned short pos)
{
    if( pos >= size_ || pos < 0 )
    {
        cout    << ERROR_SIZE_1 
                << pos 
                << ERROR_SIZE_2 
                << size_ 
                << '.' 
                << endl;
    }
    return dato_[pos];
}

simbolo & arreglo::obtener_dato(const unsigned short pos)
{
    if( pos >= size_ || pos < 0 )
    {
        cout    << ERROR_SIZE_1 
                << pos 
                << ERROR_SIZE_2 
                << size_ 
                << '.' 
                << endl;
    }
    return dato_[pos];
}

int arreglo::obtener_size() const
{
    return size_;
}

