#include "ColaSegura.h"
#include <utility>

ColaSegura::ColaSegura() : cola(), 
                           mutex(){}

OperacionEncapsulada ColaSegura::pop(){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->cola.empty()){
        throw ExcepcionColaVacia();
    }
    OperacionEncapsulada operacion = std::move(this->cola.front());
    this->cola.pop();
    return operacion;
}
void ColaSegura::push(OperacionEncapsulada operacion){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->cola.push(std::move(operacion));
}
