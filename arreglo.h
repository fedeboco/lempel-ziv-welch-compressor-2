#include <iostream>
using namespace std;

#ifndef ARREGLO_DEF
#define ARREGLO_DEF

//-------------SECUENCIA------------
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

//-------------ARREGLO------------
class arreglo
{
private:
    secuencia * dato_;
    int * size_;
    int ult_;

public:
    arreglo(const int &);
    ~arreglo();
    
    secuencia & operator[](const int);
    secuencia & get_dato(const int);
    int get_size() const;


};

//-------------DICCIONARIO------------
class diccionario
{
private:
    arreglo * dic_;
    int * size_;
    int ult_;

public:
    secuencia & obtener_secuencia(const int);
    diccionario(const int &);
    const int buscar_secuencia(const int &, const char &);
    int agregar_secuencia(const int &, const char &);
    void asignar_secuencia(const int, const secuencia &);
    void asignar_secuencia(const int pos, const int &, const char &);
    int obtener_P(const int) const;
    char obtener_S(const int) const;
    void resetear_diccionario();
};

#endif