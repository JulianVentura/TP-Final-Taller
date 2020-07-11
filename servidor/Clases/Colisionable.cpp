#include "Colisionable.h"
#include <utility>


Colisionable::Colisionable(){}

Colisionable::Colisionable(float x, float y, float ancho, float alto) : 
                          posicion(x, y, ancho, alto){}
                          
Colisionable::~Colisionable(){}


const quadtree::Box<float>& Colisionable::obtenerArea() const{
    return posicion.obtenerAreaQueOcupa();
}

const Posicion& Colisionable::obtenerPosicion() const{
    return posicion;
}

bool Colisionable::colisionaCon(const Colisionable &otro) const{
    return otro.colisionaCon(posicion.obtenerAreaQueOcupa());
}

bool Colisionable::colisionaCon(const quadtree::Box<float> &area) const{
    return posicion.obtenerAreaQueOcupa().intersects(area);
}