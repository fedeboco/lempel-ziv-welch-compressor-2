#include <iostream>
#include "secuencia.h"
using namespace std;

#ifndef ARREGLO_DEF
#define ARREGLO_DEF

//-------------------- Definición de la clase arreglo -------------------//

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
#endif