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
    /*
    TODO:
    Pensar bien en esto, quizas no conviene lanzar una excepcion en cada iteracion
    del gameloop, puede llegar a ser muy caro.
    Quizas se puede hacer un nuevo tipo de cola que contenga *operacion y que se encargue
    de liberarlas a medida que las van sacando de la cola.
    Cuando se pide un nuevo elemento de la cola se puede liberar al anterior.
    De esta forma cuando la cola se queda sin elementos puede devolver nullptr, no hay necesidad
    de usar excepciones.
    Se puede implementar utilizando una std::queue<Operacion*> y un puntero a la ultima operacion
    extraida, que sera liberada cuando se vuelva a llamar al metodo pop() 
    Ademas no se pierde memoria dinamica y ya no seria necesaria la clase OperacionEncapsulada.
    */