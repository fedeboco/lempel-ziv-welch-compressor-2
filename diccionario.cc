#include <iostream>
#include "diccionario.h"
#include "tipos_datos.h"
#include "funciones_impresion.h"


using namespace std;

diccionario::diccionario(const int & size)
{
    int size_aux = size; 
    if (size < CANT_ASCII)
    {
      imprimir_error(ERROR_SIZE_DIC);
      size_aux = CANT_ASCII;  
    }  
    dic_ = new arreglo(size_aux);
    size_ = size_aux;
}

diccionario::~diccionario()
{
    if( dic_ )
        delete dic_;
}

//Obtiene un simbolo del diccionario de tipo [ushort Prefijo, char Sufijo] y la retorna.
simbolo & diccionario::obtener_simbolo(const unsigned short i)
{
    if( i < 0 || i > ult_ )
        cout << MSJ_ERROR_OBT_SEC << endl;
    return dic_ -> obtener_dato(i);
}

//Copia un simbolo del tipo [ushort Prefijo, char Sufijo] a una posición del diccionario.
estado_t diccionario::asignar_simbolo(const unsigned short pos, const simbolo & dato)
{
    if( pos < 0 || pos > MAX_VECTOR - 1 )
        return ERROR_ASIGNAR_SEC;
    (*dic_)[pos] = dato;
    return OK;
}

//Asigna un ushort P (Prefijo) y un char S (Sufijo) a un simbolo de cierta posición del diccionario.
estado_t diccionario::asignar_simbolo(const unsigned short pos, const unsigned short & P, const char & S)
{
    if( pos < 0 || pos > MAX_VECTOR - 1 )
        return ERROR_ASIGNAR_SEC;
    (*dic_)[pos].asignarP(P);
    (*dic_)[pos].asignarS(S);
    return OK;
}

//Asigna simbolo dedicado al método de árbol
estado_t diccionario::asignar_simbolo(  const unsigned short pos, const unsigned short & P, const char & S, const unsigned short & L, const unsigned short & R, const unsigned short & PRI)
{
    if( pos < 0 || pos > MAX_VECTOR - 1 )
        return ERROR_ASIGNAR_SEC;
    (*dic_)[pos].asignarP(P);
    (*dic_)[pos].asignarS(S);
    (*dic_)[pos].asignarL(L);
    (*dic_)[pos].asignarR(R);
    (*dic_)[pos].asignarPRI(PRI);
    return OK;
}

//Asigna elemento a la posicion PRI en la posición pos
void diccionario::asignar_PRI(const unsigned short & pos, const unsigned short & PRI)
{
    (*dic_)[pos].asignarPRI(PRI);
}

//Asigna L en la posición pos
void diccionario::asignar_L(const unsigned short & pos, const unsigned short & L)
{
    (*dic_)[pos].asignarL(L);
}

//Asigna R en la posición pos
void diccionario::asignar_R(const unsigned short & pos, const unsigned short & R)
{
    (*dic_)[pos].asignarR(R);
}
//Obtiene el prefijo de cierta posición del diccionario.
unsigned short diccionario::obtener_P(const unsigned short pos) const
{
    return (*dic_)[pos].obtenerP();
}

//Obtiene el sufijo de cierta posición del diccionario.
char diccionario::obtener_S(const unsigned short pos) const 
{
    return (*dic_)[pos].obtenerS();
}

//Obtiene el primero/izquierdo de cierta posición del diccionario.
unsigned short diccionario::obtener_L(const unsigned short pos) const
{
    return (*dic_)[pos].obtenerL();
}

//Obtiene el siguiente/derecho de cierta posición del diccionario.
unsigned short diccionario::obtener_R(const unsigned short pos) const
{
    return (*dic_)[pos].obtenerR();
}

//Obtiene la ultima posición
unsigned short diccionario::obtener_ult_()
{
    return ult_;
}

//Obtiene el elemento "primero" de la posición pos
unsigned short diccionario::obtener_pri(const unsigned short pos) const
{
    return (*dic_)[pos].obtenerPri();
}

//Vacía el diccionario.
void diccionario::resetear_diccionario()
{
    this -> cargar_ASCII();
    ult_ = CANT_ASCII;
}

//Asigna un ushort P (Prefijo) y un char S (Sufijo) al simbolo de la primera posición vacía del diccionario.
unsigned short diccionario::agregar_simbolo(const unsigned short & P, const char & S)
{
    int size = size_;
    if( ult_ >= size - 2){
        cout << MSJ_DIC_LLENO << endl;
        this -> resetear_diccionario();
    }
    ult_++;
    asignar_simbolo(ult_,P,S,NULO,obtener_L(P),NULO);
    (*dic_)[P].asignarL(ult_);
    return ult_;
}

//Agrega simbolo dedicado al metodo de arbol
unsigned short diccionario::agregar_simbolo(const unsigned short & P, const char & S, const unsigned short & L, const unsigned short & R, const unsigned short & PRI)
{
    if( ult_ >= size_ - 2){
        imprimir_mensaje(MSJ_ESTADO_DIC_LLENO);
        this -> resetear_diccionario();
    }
    ult_++;
    asignar_simbolo(ult_,P,S,L,R,PRI);
    return ult_;
}

//Búsqueda del primer simbolo que coincida con el prefijo y el sufijo suministrado. Retorna índice.
const unsigned short diccionario::buscar_simbolo_lineal(const unsigned short & P, const char & S)
{
    for( int i = 0; i >= 0 && i <= size_ && i <= ult_; i++ )
    {
        if( this->obtener_P(i) == P && this->obtener_S(i) == S )
            return i;
    }
    return NULO;
}

//Busca simbolo armando una lista con dic[pos] = [P_, S_, primero=L_, siguiente=R_]
const unsigned short diccionario::buscar_simbolo_lista(const unsigned short & P, const char & S)
{
    unsigned short indice = NULO;
    if( P == NULO )
        return NULO;
    indice = this -> obtener_L( P );
    while( indice != NULO && !( obtener_P( indice )==P && obtener_S( indice )==S ) )
        indice = obtener_R( indice );
    return indice;
}

//Busca simbolo armando un arbol binario de busqueda sin balancear
const unsigned short diccionario::buscar_simbolo_arbol(const unsigned short & P, const char & S)
{
    char S_aux;
    
    if(P == NULO)
        return NULO;

    if (P > ult_)
    {
        agregar_simbolo(P,S,NULO,NULO,NULO);
        return NULO;
    }
    else
    {
        if ( obtener_pri(P) == NULO)
        {
            agregar_simbolo(P,S,NULO,NULO,NULO);
            asignar_PRI(P,ult_);
            return NULO;        
        }
        else
        {
            unsigned short pos = obtener_pri(P);
            S_aux = obtener_S(pos);
            while(1)
            {
                if(S_aux == S){
                    return pos;
                    cout << pos << endl;
                }
                else if(S_aux < S)
                {
                    if(this -> obtener_L(pos) == NULO)
                    {
                        agregar_simbolo(P,S,NULO,NULO,NULO);
                        asignar_L(pos,ult_);
                        return NULO;
                    }
                    else
                    {
                        pos = obtener_L(pos);
                        S_aux = obtener_S(pos);
                    }                    
                }
                else
                {
                    if(this -> obtener_R(pos) == NULO)
                    {
                        agregar_simbolo(P,S,NULO,NULO,NULO);
                        asignar_R(pos,ult_);
                        return NULO;    
                    }
                    else
                    {
                        pos = obtener_R(pos);
                        S_aux = obtener_S(pos);
                    }
                    
                }
                
            }
        }
    }
}   

//Devuelve el primer caracter del diccionario de la ubicación buscada.
unsigned short diccionario::obtener_indice(const unsigned short & ubic)
{
    if (ubic < CANT_ASCII + 1)
        return ubic;
    else
    {
        unsigned short aux_P;
        aux_P = this -> obtener_P(ubic);
        return  this -> obtener_indice(aux_P);
    }
        
}

//Imprime cadena de caracteres según indice.
estado_t diccionario::imprimir_indice(const unsigned short & ubic, ostream * oss)
{
    unsigned short aux_P;
    //Como el S es char va del -127 al 127 por ende del 128 al 255 los toma como negativos.
    unsigned char aux_S;
    if (ubic <= CANT_ASCII)
    {
	aux_S = this ->obtener_S(ubic);
	(*oss).write(reinterpret_cast<char*>(&aux_S),sizeof(aux_S));
    if((*oss).fail())
		return ERROR_ESCRITURA;
    }
    else
    {
        aux_P = this -> obtener_P(ubic);
        aux_S = this -> obtener_S(ubic);
        this -> imprimir_indice (aux_P, oss);
        this -> imprimir_indice (aux_S, oss);
    }
    return OK;    
}

//Carga tabla ASCII extendida desde 0 hasta 255.
bool diccionario::cargar_ASCII()
{
    for(int i=0; i<=CANT_ASCII; i++)
	    this -> asignar_simbolo(i,NULO,char(i),NULO,NULO,NULO);
    ult_ = CANT_ASCII;        
    return true;
}
