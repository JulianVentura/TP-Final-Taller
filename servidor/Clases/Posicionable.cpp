#include "Posicionable.h"
#include <utility>
#include <string>


Posicionable::Posicionable(float x, float y, float ancho, float alto) : posicion(x, y, ancho, alto){}

void Posicionable::actualizarPosicion(Posicion &&posicion){
    this->posicion.actualizarPosicion(std::move(posicion));
}

const quadtree::Box<float>& Posicionable::obtenerAreaQueOcupa(){
    return posicion.obtenerAreaQueOcupa();
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

void Posicionable::moverHaciaArriba(){
    posicion.moverHaciaArriba(desplazamiento);
}
void Posicionable::moverHaciaAbajo(){
    posicion.moverHaciaAbajo(desplazamiento);
}
void Posicionable::moverHaciaDerecha(){
    posicion.moverHaciaDerecha(desplazamiento);
}
void Posicionable::moverHaciaIzquierda(){
    posicion.moverHaciaIzquierda(desplazamiento);
}
void Posicionable::detenerse(){
    posicion.detenerse();
}
