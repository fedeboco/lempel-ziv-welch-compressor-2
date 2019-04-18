#include <iostream>
#include "secuencia.h"

using namespace std;

secuencia::secuencia()
{
    P_ = new int;
    S_ = new char;
}

secuencia::secuencia(const int & P, const char & S)
{
    P_ = new int;
    S_ = new char;

    *P_ = P;
    *S_ = S;

}

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

void secuencia::asignarP(const int & P)
{
    *P_ = P;
}

void secuencia::asignarS(const char & S)
{
    *S_ = S;
}

void secuencia::asignarPS(const int & P, const char & S)
{
    *P_ = P;
    *S_ = S;
}

int secuencia::obtenerP()
{
    return *P_;
}

char secuencia::obtenerS()
{
    return *S_;
}