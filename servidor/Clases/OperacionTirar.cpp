#include "OperacionTirar.h"
#include "Cliente.h"
#include "Personaje.h"

OperacionTirar::OperacionTirar(Cliente *unCliente,
                               unsigned int posicion) : 
                               cliente(unCliente),
                               pos(posicion){}

OperacionTirar::~OperacionTirar(){}

void OperacionTirar::ejecutar(){
    Personaje *personaje = cliente->obtenerPersonaje();
    personaje->tirar(pos);
    cliente->enviarInventario();
} 