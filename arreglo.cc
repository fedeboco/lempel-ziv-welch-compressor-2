#include <iostream>
#include "arreglo.h"

using namespace std;

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

void arreglo::asignar_dato(const int pos, const secuencia & dato)
{
    dato_[pos] = dato;
}

void arreglo::asignar_secuencia(const int pos, const int & P, const char & S)
{
    dato_[pos].setP(P);
    dato_[pos].setS(S);
}

int arreglo::obtener_P(const int pos)
{
    return dato_[pos].getP();
}

//Constructor
secuencia::secuencia()
{
    P_ = new int;
    S_ = new char;
}

//Constructor
secuencia::secuencia(const int & P, const char & S)
{
    P_ = new int;
    S_ = new char;

    *P_ = P;
    *S_ = S;

}

//Constructor copia
void secuencia::operator=(const secuencia & sec)
{
    P_ = new int;
    S_ = new char;

    *P_ = *sec.P_;
    *S_ = *sec.S_;

}

secuencia::~secuencia()
{
    delete P_;
    delete S_;
}

void secuencia::setP(const int & P)
{
    *P_ = P;
}

void secuencia::setS(const char & S)
{
    *S_ = S;
}

void secuencia::setPS(const int & P, const char & S)
{
    *P_ = P;
    *S_ = S;
}

int secuencia::getP()
{
    return *P_;
}

char secuencia::getS()
{
    return *S_;
}

