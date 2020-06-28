#include "ColaOperaciones.h"

ColaOperaciones::ColaOperaciones() : cola(),
                                     ultimaOperacion(nullptr),
                                     mutex(){}

Operacion* ColaOperaciones::pop(){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (ultimaOperacion){
        delete ultimaOperacion;
        ultimaOperacion = nullptr;
    }
    if (this->cola.empty()){
        return nullptr;
    }
    Operacion* operacion = this->cola.front();
    this->cola.pop();
    ultimaOperacion = operacion;
    return operacion;
}
void ColaOperaciones::push(Operacion* operacion){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->cola.push(operacion);
}

ColaOperaciones::~ColaOperaciones(){
    if (ultimaOperacion){
        delete ultimaOperacion;
        ultimaOperacion = nullptr;
    }
}