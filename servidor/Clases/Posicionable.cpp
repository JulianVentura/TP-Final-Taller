#include "Posicionable.h"
#include <utility>
#include <string>


Posicionable::Posicionable() : posicion(0,0){}

void Posicionable::actualizarPosicion(Posicion &&posicion){
    this->posicion = std::move(posicion);
}

const quadtree::Box<float>& Posicionable::obtenerAreaQueOcupa(){
    return posicion.obtenerAreaQueOcupa();
}

std::string Posicionable::imprimirPosicion(){
    return std::move(posicion.imprimirPosicion());
}

const Posicion& Posicionable::obtenerPosicion() const{
    return posicion;
}

const float Posicionable::obtenerX() const{
    return posicion.obtenerX();
}

const float Posicionable::obtenerY() const{
    return posicion.obtenerY();
}