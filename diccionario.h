#include <iostream>
#include "arreglo.h"
#include "simbolo.h"
using namespace std;

#ifndef DICCIONARIO_DEF
#define DICIONARIO_DEF

class diccionario
{
private:
    arreglo * dic_;
    int * size_;                               
    unsigned short ult_;

public:
    simbolo & obtener_simbolo(const unsigned short);
    diccionario(const int &);
    ~diccionario();
    const unsigned short buscar_simbolo(const unsigned short &, const char &);
    const unsigned short buscar_simbolo_lineal(const unsigned short &, const char &);
    const unsigned short buscar_simbolo_lista(const unsigned short &, const char &);
    unsigned short agregar_simbolo(const unsigned short &, const char &);
    void asignar_simbolo(const unsigned short, const simbolo &);
    void asignar_simbolo(const unsigned short, const unsigned short &, const char &);
    void asignar_simbolo(   const unsigned short, 
                            const unsigned short &, 
                            const char &,
                            const unsigned short &, 
                            const unsigned short &);
    unsigned short obtener_P(const unsigned short) const;
    unsigned short obtener_L(const unsigned short) const;
    unsigned short obtener_R(const unsigned short) const;
    unsigned short obtener_ult_();
    char obtener_S(const unsigned short) const;
    void resetear_diccionario();
    unsigned short obtener_indice(const unsigned short &);
    void imprimir_indice (const unsigned short &, ostream *);
    bool cargar_ASCII();

};
#endif