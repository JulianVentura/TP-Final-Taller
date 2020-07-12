#include "OperacionTirar.h"
#include "Cliente.h"
#include "Personaje.h"
#include <iostream>

OperacionTirar::OperacionTirar(Cliente *unCliente,
                               unsigned int posicion) : 
                               cliente(unCliente),
                               pos(posicion){}

OperacionTirar::~OperacionTirar(){
    //Do nothing
}

void OperacionTirar::ejecutar(){
    try{
        Personaje *personaje = cliente->obtenerPersonaje();
        personaje->tirar(pos);
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionTirar" << std::endl;
    }
} 