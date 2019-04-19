#include <iostream>
#include "arreglo.h"
#include "secuencia.h"

using namespace std;

arreglo::arreglo(const int & size)
{
    if( size > 0 )
    {
        dato_ = new secuencia[size];
        size_ = new int;
        *size_ = size;
    }

}

arreglo::~arreglo()
{
    delete[] dato_;
    delete size_;
}

secuencia & arreglo::operator[](const int pos)
{
    return dato_[pos];
}

secuencia & arreglo::obtener_dato(const int pos)
{
    return dato_[pos];
}

int arreglo::obtener_size() const
{
    return *size_;
}

