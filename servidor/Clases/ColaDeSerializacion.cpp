#include "ColaDeSerializacion.h"
#include "../../common/Excepcion.h"
#include <utility> 

ColaSerializacion::ColaSerializacion() : 
                        conditionVariable(), 
                        cola(), 
                        mutex(),
                        colaCerrada(false){}

SerializacionCliente ColaSerializacion::pop(){
    std::unique_lock<std::mutex> lock(this->mutex);
    while (this->cola.empty()){
        if (this->colaCerrada){
            throw Excepcion("Cola cerrada");
        }
        conditionVariable.wait(lock);
    }
    SerializacionCliente unCliente = std::move(this->cola.front());
    this->cola.pop();
    return unCliente;
}
void ColaSerializacion::push(SerializacionCliente cliente){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->colaCerrada){
        throw Excepcion("No se pueden encolar mas mensajes, la cola ha sido cerrada");
    }
    this->cola.push(std::move(cliente));
    conditionVariable.notify_all();
}

void ColaSerializacion::cerrarCola(){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->colaCerrada) return;
    this->colaCerrada = true;
    this->conditionVariable.notify_all();
}
