#include <iostream>
using namespace std;

#ifndef SECUENCIA_DEF
#define SECUENCIA_DEF

//-------------------- Declaración de la clase secuencia -------------------//
class secuencia
{
private:
    int * P_; //prefijo
    char * S_; //sufijo

public:
    secuencia();
    secuencia(const int &, const char &);
    ~secuencia();

    void operator=(const secuencia &);
    void setP(const int &);
    void setS(const char &);
    void setPS(const int &, const char &);
    int getP();
    char getS();
};
#endif