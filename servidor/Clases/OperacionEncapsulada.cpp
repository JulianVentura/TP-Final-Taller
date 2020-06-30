#include "OperacionEncapsulada.h"


OperacionEncapsulada::OperacionEncapsulada() : 
                          operacion(nullptr),
                          punteroValido(false){}

OperacionEncapsulada::OperacionEncapsulada(Operacion *unaOperacion) : 
                                           operacion(nullptr),
                                           punteroValido(false){
    if (unaOperacion){
        operacion = unaOperacion;
        punteroValido = true;
    }else{
        throw Excepcion
        ("Se ha intentado construir una operacion segura con un puntero invalido");
    }
}
OperacionEncapsulada::OperacionEncapsulada(OperacionEncapsulada &&otro) : 
                                           operacion(otro.operacion),
                                           punteroValido(false){
    if (!otro.operacion){
        throw Excepcion
        ("Se ha intentado construir una operacion segura con un puntero invalido");
    }else{
        punteroValido = true;
        otro.operacion = nullptr;
        otro.punteroValido = false;
    }
}
OperacionEncapsulada& OperacionEncapsulada::operator=(OperacionEncapsulada &&otro){
    if (!otro.operacion){
        throw Excepcion
        ("Se ha intentado copiar una operacion segura con un puntero invalido");
    }else{
        if (punteroValido){
            delete this->operacion;
        }
        this->operacion = otro.operacion;
        punteroValido = true;
        otro.operacion = nullptr;
        otro.punteroValido = false;
    }
    return *this;
}
OperacionEncapsulada::~OperacionEncapsulada(){
    if (punteroValido){
        delete operacion;
        punteroValido = false;
    }
}
Operacion* OperacionEncapsulada::obtenerOperacion(){
    if (punteroValido){
        return operacion;
    }else{
        throw Excepcion
        ("Se ha intentado obtener un puntero operacion, pero ninguno fue asignado");
    }
}
