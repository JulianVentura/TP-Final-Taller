#ifndef __COLISIONABLE__
#define __COLISIONABLE__
#include "Rectangulo.h"

class Colisionable{
    private:
    Rectangulo area;
    public:
    Colisionable(Rectangulo &&rectangulo);
    Colisionable(Colisionable &&otro) = delete;
    Colisionable(Colisionable &otro) = delete;
    Colisionable& operator=(Colisionable &&otro) = delete;
    Colisionable& operator=(Colisionable &otro) = delete;
    Rectangulo& obtenerArea();
    bool colisionaCon(Colisionable &otro);


};
#endif
