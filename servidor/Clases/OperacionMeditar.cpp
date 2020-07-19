#include "OperacionMeditar.h"
#include "Cliente.h"
#include "Personaje.h"
#include <iostream>

OperacionMeditar::OperacionMeditar(Cliente *unCliente) : 
                                   cliente(unCliente){}

OperacionMeditar::~OperacionMeditar(){
    //Do nothing
}

void OperacionMeditar::ejecutar(){
    Personaje *personaje = cliente->obtenerPersonaje();
    personaje->meditar();
} 