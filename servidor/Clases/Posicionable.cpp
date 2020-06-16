#include "Posicionable.h"
#include <utility>
#include <string>


Posicionable::Posicionable() : posicion(0,0){}

void Posicionable::actualizarPosicion(Posicion &&posicion){
    this->posicion = std::move(posicion);
}

Rectangulo& Posicionable::obtenerAreaQueOcupa(){
    return posicion.obtenerAreaQueOcupa();
}

std::string Posicionable::imprimirPosicion(){
    return std::move(posicion.imprimirPosicion());
}