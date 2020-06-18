#include "ColaBloqueante.h"
#include "ExcepcionColaCerrada.h"
#include <utility> //Me lo pide el SERCOM para usar std::move

ColaBloqueante::ColaBloqueante() : conditionVariable(), 
                                   cola(), 
                                   mutex(),
                                   colaCerrada(false){}

Operacion* ColaBloqueante::pop(){
    std::unique_lock<std::mutex> lock(this->mutex);
    while (this->cola.empty()){
        if (this->colaCerrada){
            throw ExcepcionColaCerrada();
        }
        conditionVariable.wait(lock);
    }
    Operacion *operacion = this->cola.front();
    this->cola.pop();
    return operacion;
}
void ColaBloqueante::push(Operacion *operacion){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->cola.push(operacion);
    conditionVariable.notify_all();
}

void ColaBloqueante::cerrarCola(){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->colaCerrada = true;
    this->conditionVariable.notify_all();
}
