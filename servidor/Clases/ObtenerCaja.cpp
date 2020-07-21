#include "ObtenerCaja.h"

quadtree::Box<float> ObtenerCaja::operator()(Colisionable* const &unColisionable) const{
    return unColisionable->obtenerArea();
}