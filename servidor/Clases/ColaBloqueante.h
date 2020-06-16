#ifndef __COLA_BLOQUEANTE__
#define __COLA_BLOQUEANTE__

#include "Operacion.h"
#include <condition_variable>
#include <mutex>
#include <queue>


class ColaBloqueante{
    private:
    std::condition_variable conditionVariable;
    std::queue<Operacion*> cola;
    std::mutex mutex;
    bool colaCerrada;

    public:
    ColaBloqueante();
    /*
    Obtiene un objeto Operacion de la cola bloqueante por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Este metodo es bloqueante, en caso de que la cola no contenga objetos
    Operacion se mandara a dormir al thread.
    */
    Operacion* pop();
    /*
    Guarda un objeto Operacion en la cola bloqueante por movimiento.
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    Al finalizar su ejecucion avisara a los threads en espera que un 
    nuevo material ha sido ingresado a la cola.
    En caso de que la cola haya sido cerrada lanzara la excepcion
    ExcepcionColaCerrada
    */
    void push(Operacion *operacion);
    /*
    Cierra la cola bloqueante y despierta a los threads en espera
    Este metodo es thread safe, por lo tanto no existiran conflictos
    en ejecuciones concurrentes.
    */
    void cerrarCola();
};

#endif
