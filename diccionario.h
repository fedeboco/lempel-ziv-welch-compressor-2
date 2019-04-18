#include <iostream>
#include "arreglo.h"
#include "secuencia.h"
using namespace std;

#ifndef DICCIONARIO_DEF
#define DICIONARIO_DEF

//-------------------- Declaración de la clase diccionario -------------------//

class diccionario
{
private:
    arreglo * dic_;
    int * size_;                               
    int ult_;

public:
    secuencia & obtener_secuencia(const int);
    diccionario(const int &);
    ~diccionario();
    const int buscar_secuencia(const int &, const char &);
    int agregar_secuencia(const int &, const char &);
    void asignar_secuencia(const int, const secuencia &);
    void asignar_secuencia(const int pos, const int &, const char &);
    int obtener_P(const int) const;
    char obtener_S(const int) const;
    void resetear_diccionario();
    int obtener_indice(const int &);
    bool buscar_indice(const int &, int *);
    void imprimir_indice (const int &, ostream *);
    bool agregar_secuencia(const int &, const char &, int *);
    bool cargar_ASCII (int = 255);

};
#endif