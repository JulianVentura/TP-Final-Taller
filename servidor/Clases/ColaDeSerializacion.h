#ifndef __COLA_DE_SERIALIZACION_H__
#define __COLA_DE_SERIALIZACION_H__

#include "../../common/Serializacion.h"
#include <condition_variable>
#include <mutex>
#include <queue>


class ColaSerializacion{
    private:
    std::condition_variable conditionVariable;
    std::queue<SerializacionCliente> cola;
    std::mutex mutex;
    bool colaCerrada;

    public:
    ColaSerializacion();
    /*
    Obtiene un objeto SerializacionCliente de la cola bloqueante por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Este metodo es bloqueante, en caso de que la cola no contenga objetos
    Mensaje se mandara a dormir al thread.
    */
    SerializacionCliente pop();
    /*
    Guarda un objeto SerializacionCliente en la cola bloqueante por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Al finalizar su ejecucion avisara a los threads en espera que un 
    nuevo mensaje ha sido ingresado a la cola.
    En caso de que la cola haya sido cerrada lanzara la excepcion
    Excepcion.
    */
    void push(SerializacionCliente mensaje);
    /*
    Cierra la cola bloqueante y despierta a los threads en espera
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    */
    void cerrarCola();
};

#endif
