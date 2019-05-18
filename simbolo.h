#include <iostream>
using namespace std;

#ifndef simbolo_DEF
#define simbolo_DEF

class simbolo
{
private:
    unsigned short P_; //prefijo
    char S_; //sufijo
    unsigned short L_; //primero o izquierda
    unsigned short R_; //siguiente o derecha
    unsigned short PRI_;

public:
    simbolo();
    simbolo(const unsigned short &, const char &);

    void operator=(const simbolo &);
    void asignarP(const unsigned short &);
    void asignarS(const char &);
    void asignarPS(const unsigned short &, const char &);
    unsigned short obtenerP();
    char obtenerS();
    void asignarL(const unsigned short &);
    void asignarR(const unsigned short &);
    void asignarLR(const unsigned short &, const unsigned short &);
    void asignarPRI(const unsigned short &);
    unsigned short obtenerL();
    unsigned short obtenerR();
    unsigned short obtenerPri();
};
#endif