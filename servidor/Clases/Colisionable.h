#ifndef __COLISIONABLE_H__
#define __COLISIONABLE_H__
#include "Box.h"
#include "Posicion.h"

class Colisionable{
    protected:
    Posicion posicion;
    
    public:
    Colisionable();
    Colisionable(float x, float y, float ancho, float alto);
    Colisionable(Colisionable &&otro) = delete;
    Colisionable(Colisionable &otro) = delete;
    Colisionable& operator=(Colisionable &&otro) = delete;
    Colisionable& operator=(Colisionable &otro) = delete;
    virtual ~Colisionable();
    virtual const quadtree::Box<float>& obtenerArea() const;
    virtual bool colisionaCon(const Colisionable &otro) const;
    virtual bool colisionaCon(const quadtree::Box<float> &area) const;
    virtual const Posicion& obtenerPosicion() const;
};

#endif
