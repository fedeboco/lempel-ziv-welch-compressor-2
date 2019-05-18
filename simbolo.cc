#include <iostream>
#include "simbolo.h"

using namespace std;

simbolo::simbolo()
{
    P_ = new unsigned short;
    S_ = new char;
    L_ = new unsigned short;
    R_ = new unsigned short;
    PRI_ = new unsigned short;
}

simbolo::simbolo(const unsigned short & P, const char & S)
{
    P_ = new unsigned short;
    S_ = new char;

    *P_ = P;
    *S_ = S;

}

//Constructor copia de simbolos.
void simbolo::operator=(const simbolo & sim)
{
    P_ = new unsigned short;
    S_ = new char;

    *P_ = *sim.P_;
    *S_ = *sim.S_;
}

simbolo::~simbolo()
{
    if( P_ )
        delete P_;
    if( S_ )
        delete S_;
    if( L_ )
        delete L_;
    if( R_ )
        delete R_;
    if( PRI_ )
        delete PRI_;    
}

//Asigna sólo el prefijo a la simbolo.
void simbolo::asignarP(const unsigned short & P)
{
    *P_ = P;
}

//Asigna sólo el sufijo a la simbolo.
void simbolo::asignarS(const char & S)
{
    *S_ = S;
}

//Asigna prefijo y sufijo a la simbolo.
void simbolo::asignarPS(const unsigned short & P, const char & S)
{
    *P_ = P;
    *S_ = S;
}

//Extrae el prefijo de la simbolo.
unsigned short simbolo::obtenerP()
{
    return *P_;
}

//Extrae el sufijo de la simbolo.
char simbolo::obtenerS()
{
    return *S_;
}

//Asigna sólo el prefijo a la simbolo.
void simbolo::asignarL(const unsigned short & L)
{
    *L_ = L;
}

//Asigna sólo el sufijo a la simbolo.
void simbolo::asignarR(const unsigned short & R)
{
    *R_ = R;
}

//Asigna prefijo y sufijo a la simbolo.
void simbolo::asignarLR(const unsigned short & L, const unsigned short & R)
{
    *L_ = L;
    *R_ = R;
}

void simbolo::asignarPRI(const unsigned short &PRI)
{
    *PRI_ = PRI;
}

//Extrae el prefijo de la simbolo.
unsigned short simbolo::obtenerL()
{
    return *L_;
}

//Extrae el sufijo de la simbolo.
unsigned short simbolo::obtenerR()
{
    return *R_;
}

unsigned short simbolo::obtenerPri()
{
    return *PRI_;
}