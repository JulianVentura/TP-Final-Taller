#include "Interactuable.h"
#define DIST_INTERACCION 50





Interactuable::Interactuable(std::string unId) : 
                                      id(unId),
                                      distanciaMaximaDeInteraccion(DIST_INTERACCION){
    //La distancia maxima de interaccion deberia ser levantada del json.
}

const quadtree::Box<float>& Interactuable::obtenerArea() const{
    return this->posicion.obtenerAreaQueOcupa();
}

bool Interactuable::colisionaCon(const Colisionable &otro) const{
    return otro.colisionaCon(this->posicion.obtenerAreaQueOcupa());
}

bool Interactuable::colisionaCon(const quadtree::Box<float> &area) const{
    return this->posicion.obtenerAreaQueOcupa().intersects(area);
}

const std::string Interactuable::obtenerId() const{
    return id + "#";
}

const Posicion& Interactuable::obtenerPosicion() const{
    return this->posicion;
}

Interactuable::~Interactuable(){}