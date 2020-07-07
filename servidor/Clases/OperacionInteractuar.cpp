#include "OperacionInteractuar.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Interactuable.h"
#include <iostream> //DEBUG

OperacionInteractuar::OperacionInteractuar(Cliente *unCliente, 
                                 Mapa *unMapa,
                                 std::string id) : 
                                 cliente(unCliente),
                                 mapa(unMapa),
                                 idObjetivo(id){}

OperacionInteractuar::~OperacionInteractuar(){
    //Do nothing
}

void OperacionInteractuar::ejecutar(){
    try{
        Interactuable *interactuable = mapa->obtenerInteractuable(idObjetivo);
        Personaje *personaje = cliente->obtenerPersonaje();
        Estado *estado = personaje->obtenerEstado();
        interactuable->interactuar(estado, cliente);
    }catch(std::exception &e){
        cliente->enviarChat(e.what(), false);
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
}  