#include "Movible.h"
#include <utility>
#include <string>


Movible::Movible() : desplazamiento(0){}

Movible::Movible(float x, float y, float ancho, float alto) : Colisionable(x, y, ancho, alto){}

void Movible::actualizarPosicion(Posicion &&posicion){
    this->posicion.actualizarPosicion(std::move(posicion));
}

void Movible::moverHaciaArriba(){
    posicion.moverHaciaArriba(desplazamiento);
}
void Movible::moverHaciaAbajo(){
    posicion.moverHaciaAbajo(desplazamiento);
}
void Movible::moverHaciaDerecha(){
    posicion.moverHaciaDerecha(desplazamiento);
}
void Movible::moverHaciaIzquierda(){
    posicion.moverHaciaIzquierda(desplazamiento);
}
void Movible::detenerse(){
    posicion.detenerse();
}
