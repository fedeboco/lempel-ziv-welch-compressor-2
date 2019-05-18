#include <iostream>
#include "arreglo.h"
#include "simbolo.h"
#include "tipos_datos.h"
using namespace std;

#ifndef DICCIONARIO_DEF
#define DICIONARIO_DEF

class diccionario;

typedef const unsigned short (diccionario::*ptr_busqueda)(const unsigned short &, const char &);

class diccionario
{
private:
    arreglo * dic_;
    int size_;                               
    unsigned short ult_;

public:
    simbolo & obtener_simbolo(const unsigned short);
    diccionario(const int &);
    ~diccionario();
    const unsigned short buscar_simbolo_lineal(const unsigned short &, const char &);
    const unsigned short buscar_simbolo_lista(const unsigned short &, const char &);
    const unsigned short buscar_simbolo_arbol(const unsigned short & , const char & );
    unsigned short agregar_simbolo(const unsigned short &, const char &);
    unsigned short agregar_simbolo(const unsigned short & , const char & , const unsigned short & , const unsigned short & , const unsigned short & ); //Sobrecargo esta función, la idea es fucionarla con la de arriba
    estado_t asignar_simbolo(const unsigned short, const simbolo &);
    estado_t asignar_simbolo(const unsigned short, const unsigned short &, const char &);
    estado_t asignar_simbolo(const unsigned short, const unsigned short &, const char &, const unsigned short &, const unsigned short &, const unsigned short &); //sobrecargo esta función, la idea es fcionarla con la dearriba                        
    void asignar_PRI(const unsigned short &, const unsigned short & );
    void asignar_L(const unsigned short &, const unsigned short & );
    void asignar_R(const unsigned short &, const unsigned short & );
    unsigned short obtener_P(const unsigned short) const;
    unsigned short obtener_L(const unsigned short) const;
    unsigned short obtener_R(const unsigned short) const;
    unsigned short obtener_ult_();
    char obtener_S(const unsigned short) const;
    unsigned short obtener_pri(const unsigned short) const;
    void resetear_diccionario();
    unsigned short obtener_indice(const unsigned short &);
    estado_t imprimir_indice (const unsigned short &, ostream *);
    bool cargar_ASCII();

};
#endif