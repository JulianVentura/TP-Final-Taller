#include "OperacionUtilizar.h"
#include "Cliente.h"
#include "Personaje.h"

OperacionUtilizar::OperacionUtilizar(Cliente *unCliente,
                                     uint16_t posicion) : 
                                     cliente(unCliente),
                                     pos(posicion){}

OperacionUtilizar::~OperacionUtilizar(){}

void OperacionUtilizar::ejecutar(){
    Personaje *personaje = cliente->obtenerPersonaje();
    personaje->utilizar(pos);
    cliente->enviarInventario();
}