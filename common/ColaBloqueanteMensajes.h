#ifndef __COLA_BLOQUEANTE__
#define __COLA_BLOQUEANTE__

#include "Mensaje.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <queue>


class ColaBloqueanteMensajes{
    private:
    std::condition_variable conditionVariable;
    std::queue<Mensaje> cola;
    std::mutex mutex;
    bool colaCerrada;
    std::atomic<uint32_t> tamanioBytesAlmacenados;

    public:
    ColaBloqueanteMensajes();
    /*
    Obtiene un objeto Mensaje de la cola bloqueante por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Este metodo es bloqueante, en caso de que la cola no contenga objetos
    Mensaje se mandara a dormir al thread.
    */
    Mensaje pop();
    /*
    Guarda un objeto Mensaje en la cola bloqueante por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Al finalizar su ejecucion avisara a los threads en espera que un 
    nuevo mensaje ha sido ingresado a la cola.
    En caso de que la cola haya sido cerrada lanzara la excepcion
    Excepcion.
    */
    void push(Mensaje mensaje);
    /*
    Cierra la cola bloqueante y despierta a los threads en espera
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    */
    void cerrarCola();
    /*
    Devuleve la cantidad de bytes almacenados dentro de la cola en base al tamanio
    de los mensajes que han sido introducidos.
    */
    uint32_t obtenerTamBytesAlmacenados();
};

#endif
