#include <iostream>
#include "simbolo.h"
using namespace std;

#ifndef ARREGLO_DEF
#define ARREGLO_DEF

class arreglo
{
private:
    simbolo * dato_;
    int size_;
    unsigned short ult_;

public:
    arreglo(const int &);
    ~arreglo();
    
    simbolo & operator[](const unsigned short);
    simbolo & obtener_dato(const unsigned short);
    int obtener_size() const;


};
#endif