#include "OperacionResucitar.h"
#include "Cliente.h"
#include "Mapa.h"
#include "Personaje.h"

OperacionResucitar::OperacionResucitar(Cliente *unCliente, Mapa *unMapa) : 
                                       cliente(unCliente),
                                       mapa(unMapa){}

OperacionResucitar::~OperacionResucitar(){
    //Do nothing
}

void OperacionResucitar::ejecutar(){
    Personaje *personaje = cliente->obtenerPersonaje();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    double penalidad = config->obtenerPenalizacionRevivir(mapa, personaje);
    personaje->resucitar(penalidad);
    std::string ciudad = config->obtenerCiudadMasCercana(mapa->obtenerId());
    cliente->cambiarDeMapa(ciudad, config->obtenerPuntoSpawnResurreccion(ciudad));
} 