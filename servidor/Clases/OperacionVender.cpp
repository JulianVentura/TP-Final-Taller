#include "OperacionVender.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"

OperacionVender::OperacionVender(Cliente *unCliente, 
                                 Mapa *unMapa, 
                                 unsigned int pos, 
                                 std::string id) : 
                                 cliente(unCliente),
                                 mapa(unMapa),
                                 idObjetivo(id),
                                 posItem(pos){}

OperacionVender::~OperacionVender(){}

void OperacionVender::ejecutar(){
    Entidad *entidad = mapa->obtener(idObjetivo);
    Personaje *personaje = cliente->obtenerPersonaje();
    Estado *estado = personaje->obtenerEstado();
    entidad->vender(posItem, estado, cliente);
}   