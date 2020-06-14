#ifndef __COLISIONABLE__
#define __COLISIONABLE__
#include "Rectangulo.h"

class Colisionable{
    public:
    Colisionable();
    Colisionable(Colisionable &&otro) = delete;
    Colisionable(Colisionable &otro) = delete;
    Colisionable& operator=(Colisionable &&otro) = delete;
    Colisionable& operator=(Colisionable &otro) = delete;
    virtual ~Colisionable();
    virtual Rectangulo& obtenerArea() = 0;
    virtual bool colisionaCon(Colisionable &otro) = 0;
    virtual bool colisionaCon(Rectangulo &area) = 0;
};

#endif
