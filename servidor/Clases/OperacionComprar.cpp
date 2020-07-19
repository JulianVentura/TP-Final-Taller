#include "OperacionComprar.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"

OperacionComprar::OperacionComprar(Cliente *unCliente, 
                                 Mapa *unMapa, 
                                 unsigned int pos, 
                                 std::string id) : 
                                 cliente(unCliente),
                                 mapa(unMapa),
                                 idObjetivo(id),
                                 posItem(pos){}

OperacionComprar::~OperacionComprar(){
    //Do nothing
}

void OperacionComprar::ejecutar(){
    Entidad *entidad = mapa->obtener(idObjetivo);
    Personaje *personaje = cliente->obtenerPersonaje();
    Estado *estado = personaje->obtenerEstado();
    entidad->comprar(posItem, estado, cliente);
}   