#ifndef __OBTENER_CAJA_H__
#define __OBTENER_CAJA_H__
#include "Box.h"
#include "Colisionable.h"

class ObtenerCaja{
    public:
    quadtree::Box<float> operator()(Colisionable* const &) const;
};


#endif
