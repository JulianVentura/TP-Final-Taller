#include "OperacionResucitar.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Interactuable.h"
#include <iostream> //DEBUG

OperacionResucitar::OperacionResucitar(Cliente *unCliente, Mapa *unMapa) : 
                                       cliente(unCliente),
                                       mapa(unMapa){}

OperacionResucitar::~OperacionResucitar(){
    //Do nothing
}

void OperacionResucitar::ejecutar(){
    try{
        /*
        Entidad *entidad = mapa->obtener(idObjetivo);
        Personaje *personaje = cliente->obtenerPersonaje();
        Estado *estado = personaje->obtenerEstado();
        entidad->transaccion(esDeposito, estado, cliente);
        */
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
} 