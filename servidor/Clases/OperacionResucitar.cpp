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
        Personaje *personaje = cliente->obtenerPersonaje();
        Configuraciones *config = Configuraciones::obtenerInstancia();
        double penalidad = config->obtenerPenalizacionRevivir(mapa, personaje);
        personaje->resucitar(penalidad);
        std::string ciudad = config->obtenerCiudadMasCercana(mapa->obtenerId());
        cliente->cambiarDeMapa(ciudad,
                               config->obtenerPuntoSpawnResurreccion(ciudad));
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
} 