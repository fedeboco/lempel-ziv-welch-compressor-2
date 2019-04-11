#include <iostream>
#include "arreglo.h"

using namespace std;

//-----------------DICCIONARIO----------------------

diccionario::diccionario(const int & size)
{
    dic_ = new arreglo(size);
    size_ = new int;
    *size_ = size;
}

secuencia & diccionario::obtener_secuencia(const int i)
{
    return (*this).dic_->get_dato(i);
}

void diccionario::asignar_secuencia(const int pos, const secuencia & dato)
{
    (*dic_)[pos] = dato;
}

void diccionario::asignar_secuencia(const int pos, const int & P, const char & S)
{
    (*dic_)[pos].setP(P);
    (*dic_)[pos].setS(S);
}

int diccionario::obtener_P(const int pos) const
{
    return (*dic_)[pos].getP();
}

char diccionario::obtener_S(const int pos) const 
{
    return (*dic_)[pos].getS();
}

void diccionario::resetear_diccionario()
{
    int i_max = *size_ - 1;
    for(int i = 256; i <= i_max; i++)
    {
        this->asignar_secuencia(i, -2, -2);
    }
    (*this).ult_ = 255;

}

int diccionario::agregar_secuencia(const int & P, const char & S)
{
    int size = *size_;
    if( (*this).ult_ >= size ){
        this -> resetear_diccionario();
        (*this).ult_ = 255;
    }

    this->asignar_secuencia((*this).ult_ + 1, P, S);
    (*this).ult_++;
    
    return (*this).ult_; //retorna última posición agregada
}

bool diccionario::agregar_secuencia(const int & P, const char & S, int *cont)
{
    if(*cont== *size_ +1)
    {
        this -> resetear_diccionario();
        return false;
    }
    this->asignar_secuencia(++(*cont), P, S);
    return true;
}

const int diccionario::buscar_secuencia(const int & P, const char & S)
{
    int size = *size_;
    for( int i = 0; i >= 0 && i <= size && this->obtener_P(i) != -2; i++ )
    {
        if(this->obtener_P(i) == P && this->obtener_S(i) == S)
            return i;
    }
    return -1;
}

int diccionario::obtener_indice(const int & ubic)
{
    if (ubic < 256)
        return ubic;
    else
    {
        int aux_P;
        aux_P = this -> obtener_P(ubic);
        this -> obtener_indice(aux_P);
    }
    
}

bool diccionario::buscar_indice(const int & S, int * ubic)
{
    int size = *size_;
    if (S < 256)
    {
        for(*ubic = 0; *ubic <= size;(*ubic)++)
        {
            //cout << "Ubicación: " << *ubic << endl;
            if(this -> obtener_S(*ubic) == S)
                return true;
        }
    }
    else
    {
        for(*ubic = 255; *ubic <= size;(*ubic)++)
        {
            if(this -> obtener_P(*ubic) == S)
                return true;
        }
    }
    
    return false;
}

void diccionario::imprimir_indice (const int & ubic, ostream * oss)
{
    int aux_P, aux_S;
    if (ubic <= 255)
        *oss << "Indice: " << ubic << ", corresponde a:" << this -> obtener_S(ubic) << endl;
    else
    {
        *oss << "Indice: "<< ubic << endl;
        aux_P = this -> obtener_P(ubic);
        aux_S = this -> obtener_S(ubic);
        this -> imprimir_indice (aux_P, oss);
        this -> imprimir_indice (aux_S, oss);
    }
        
}


//-----------------ARREGLO----------------------
//Constructor
arreglo::arreglo(const int & size)
{
    if( size > 0 )
    {
        dato_ = new secuencia[size];
        size_ = new int;
        *size_ = size;
    }

}

//Destructor
arreglo::~arreglo()
{
    delete[] dato_;
    delete size_;
}

//Indexación
secuencia & arreglo::operator[](const int pos)
{
    return dato_[pos];
}

secuencia & arreglo::get_dato(const int pos)
{
    return dato_[pos];
}

int arreglo::get_size() const
{
    return *size_;
}

//-----------------SECUENCIA----------------------

//Constructor
secuencia::secuencia()
{
    P_ = new int;
    S_ = new char;
}

//Constructor
secuencia::secuencia(const int & P, const char & S)
{
    P_ = new int;
    S_ = new char;

    *P_ = P;
    *S_ = S;

}

//Constructor copia
void secuencia::operator=(const secuencia & sec)
{
    P_ = new int;
    S_ = new char;

    *P_ = *sec.P_;
    *S_ = *sec.S_;

}

secuencia::~secuencia()
{
    delete P_;
    delete S_;
}

void secuencia::setP(const int & P)
{
    *P_ = P;
}

void secuencia::setS(const char & S)
{
    *S_ = S;
}

void secuencia::setPS(const int & P, const char & S)
{
    *P_ = P;
    *S_ = S;
}

int secuencia::getP()
{
    return *P_;
}

char secuencia::getS()
{
    return *S_;
}

