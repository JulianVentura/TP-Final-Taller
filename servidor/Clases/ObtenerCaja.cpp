#include "ObtenerCaja.h"

quadtree::Box<float> ObtenerCaja::operator()(Colisionable* const &unColisionable) const{
    //quadtree::Box<float> caja = unColisionable.obtenerArea();
    return unColisionable->obtenerArea();
}