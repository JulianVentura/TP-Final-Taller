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
        Entidad *entidad = mapa->obtener(idObjetivo);
        Personaje *personaje = cliente->obtenerPersonaje();
        Estado *estado = personaje->obtenerEstado();
        entidad->interactuar(estado, cliente);
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
}  