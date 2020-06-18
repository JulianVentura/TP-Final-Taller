#ifndef __COLA_SEGURA__
#define __COLA_SEGURA__

#include "OperacionEncapsulada.h"
#include "ExcepcionColaVacia.h"
#include <mutex>
#include <queue>


class ColaSegura{
    private:
    std::queue<OperacionEncapsulada> cola;
    std::mutex mutex;

    public:
    ColaSegura();
    /*
    Obtiene un objeto OperacionEncapsulada de la cola por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Se lanzara una instancia de ExcepcionColaVacia si la cola no tiene elementos
    */
    OperacionEncapsulada pop();
    /*
    Guarda un objeto OperacionEncapsulada en la cola por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    */
    void push(OperacionEncapsulada operacion);
};

#endif
