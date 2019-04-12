#include <iostream>
#include "arreglo.h"
#include "secuencia.h"

using namespace std;

//-------------------- Definición de la clase arreglo -------------------//

//Constructor
arreglo::arreglo(const int & size)
{
    if( size > 0 )
    {
        dato_ = new secuencia[size];
        size_ = new int;
        *size_ = size;
    }

}

//Destructor
arreglo::~arreglo()
{
    delete[] dato_;
    delete size_;
}

//Indexación
secuencia & arreglo::operator[](const int pos)
{
    return dato_[pos];
}

secuencia & arreglo::get_dato(const int pos)
{
    return dato_[pos];
}

int arreglo::get_size() const
{
    return *size_;
}

