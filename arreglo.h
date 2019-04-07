#include <iostream>
using namespace std;

#ifndef ARREGLO_DEF
#define ARREGLO_DEF

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





class arreglo
{
private:
    secuencia * dato_;
    int * size_;

public:
    arreglo(const int  &);
    ~arreglo();
    
    void asignar_dato(const int, const secuencia &);
    void asignar_secuencia(const int pos, const int &, const char &);
    int obtener_P(const int);
    secuencia & operator[](const int);
    secuencia & get_dato(const int);

};

#endif