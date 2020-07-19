#ifndef __COLA_DE_ENTIDADES_H__
#define __COLA_DE_ENTIDADES_H__
#include "Entidad.h"
#include <queue>
#include <mutex>
class ColaDeEntidades{
    private:
    std::queue<Entidad*> cola;
    std::mutex mutex;

    public:
    ColaDeEntidades();
    ~ColaDeEntidades();
    /*
    Obtiene un puntero a Entidad de la cola.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Se devolvera nullptr si la cola esta vacia.
    */
    Entidad* pop();
    /*
    Guarda un puntero a Entidad en la cola por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    */
    void push(Entidad* entidad);
};

#endif