#include <iostream>
#include "simbolo.h"

using namespace std;

simbolo::simbolo()
{
    P_ = 0;
    S_ = 0;
    L_ = 0;
    R_ = 0;
    PRI_ = 0;
}

simbolo::simbolo(const unsigned short & P, const char & S)
{
    P_ = P;
    S_ = S;
}

//Constructor copia de simbolos.
void simbolo::operator=(const simbolo & sim)
{
    P_ = sim.P_;
    S_ = sim.S_;
}

//Asigna sólo el prefijo a la simbolo.
void simbolo::asignarP(const unsigned short & P)
{
    P_ = P;
}

//Asigna sólo el sufijo a la simbolo.
void simbolo::asignarS(const char & S)
{
    S_ = S;
}

//Asigna prefijo y sufijo a la simbolo.
void simbolo::asignarPS(const unsigned short & P, const char & S)
{
    P_ = P;
    S_ = S;
}

//Extrae el prefijo de la simbolo.
unsigned short simbolo::obtenerP()
{
    return P_;
}

//Extrae el sufijo de la simbolo.
char simbolo::obtenerS()
{
    return S_;
}

//Asigna sólo el prefijo a la simbolo.
void simbolo::asignarL(const unsigned short & L)
{
    L_ = L;
}

//Asigna sólo el sufijo a la simbolo.
void simbolo::asignarR(const unsigned short & R)
{
    R_ = R;
}

//Asigna prefijo y sufijo a la simbolo.
void simbolo::asignarLR(const unsigned short & L, const unsigned short & R)
{
    L_ = L;
    R_ = R;
}

void simbolo::asignarPRI(const unsigned short &PRI)
{
    PRI_ = PRI;
}

//Extrae el prefijo de la simbolo.
unsigned short simbolo::obtenerL()
{
    return L_;
}

//Extrae el sufijo de la simbolo.
unsigned short simbolo::obtenerR()
{
    return R_;
}

unsigned short simbolo::obtenerPri()
{
    return PRI_;
}