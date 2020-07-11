#include "OperacionVender.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Interactuable.h"
#include <iostream> //DEBUG

OperacionVender::OperacionVender(Cliente *unCliente, 
                                 Mapa *unMapa, 
                                 unsigned int pos, 
                                 std::string id) : 
                                 cliente(unCliente),
                                 mapa(unMapa),
                                 idObjetivo(id),
                                 posItem(pos){}

OperacionVender::~OperacionVender(){
    //Do nothing
}

void OperacionVender::ejecutar(){
    try{
        Entidad *entidad = mapa->obtener(idObjetivo);
        Personaje *personaje = cliente->obtenerPersonaje();
        Estado *estado = personaje->obtenerEstado();
        entidad->vender(posItem, estado, cliente);
    }catch(std::exception &e){
        //std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
}   