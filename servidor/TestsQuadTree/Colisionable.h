#ifndef __COLISIONABLE__
#define __COLISIONABLE__
#include "Box.h"

class Colisionable{
    public:
    Colisionable();
    Colisionable(Colisionable &&otro) = delete;
    Colisionable(Colisionable &otro) = delete;
    Colisionable& operator=(Colisionable &&otro) = delete;
    Colisionable& operator=(Colisionable &otro) = delete;
    virtual ~Colisionable();
    virtual const quadtree::Box<float>& obtenerArea() const = 0;
    virtual bool colisionaCon(const Colisionable &otro) const = 0;
    virtual bool colisionaCon(const quadtree::Box<float> &area) const = 0;
};

#endif
