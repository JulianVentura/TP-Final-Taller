#include "OperacionUtilizar.h"
#include "Cliente.h"
#include "Personaje.h"
#include <iostream>

OperacionUtilizar::OperacionUtilizar(Cliente *unCliente,
                                     uint16_t posicion) : 
                                     cliente(unCliente),
                                     pos(posicion){}

OperacionUtilizar::~OperacionUtilizar(){
    //Do nothing
}

void OperacionUtilizar::ejecutar(){
    try{
        Personaje *personaje = cliente->obtenerPersonaje();
        personaje->utilizar(pos);
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionUtilizar" << std::endl;
    }
}