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
    try{
        Personaje *personaje = cliente->obtenerPersonaje();
        personaje->meditar();
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionMeditar" << std::endl;
    }
} 