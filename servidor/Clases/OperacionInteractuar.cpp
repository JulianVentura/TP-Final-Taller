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
    Entidad *entidad = mapa->obtener(idObjetivo);
    Personaje *personaje = cliente->obtenerPersonaje();
    Estado *estado = personaje->obtenerEstado();
    entidad->interactuar(estado, cliente);
}  