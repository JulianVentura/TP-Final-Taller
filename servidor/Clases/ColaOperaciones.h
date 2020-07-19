#ifndef __COLA_OPERACIONES_H__
#define __COLA_OPERACIONES_H__
#include "Operacion.h"
#include <queue>
#include <mutex>
class ColaOperaciones{
    private:
    std::queue<Operacion*> cola;
    Operacion *ultimaOperacion;
    std::mutex mutex;

    public:
    ColaOperaciones();
    ~ColaOperaciones();
    /*
    Obtiene un puntero a Operacion de la cola.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Se devolvera nullptr si la cola esta vacia.
    */
    Operacion* pop();
    /*
    Guarda un puntero a Operacion en la cola por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    El puntero a Operacion sera liberado luego de que se llame a pop en el elemento
    siguiente de la cola.
    */
    void push(Operacion* operacion);
};


#endif