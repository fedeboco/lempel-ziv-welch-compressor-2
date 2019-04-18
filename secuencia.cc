#include <iostream>
#include "secuencia.h"

using namespace std;

//-------------------- Definición de la clase secuencia -------------------//

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