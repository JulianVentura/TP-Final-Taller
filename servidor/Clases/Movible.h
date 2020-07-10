#ifndef __MOVIBLE_H__
#define __MOVIBLE_H__
#include "Colisionable.h"

class Movible : public Colisionable{
    protected:
    float desplazamiento;

    public:
    Movible();
    Movible(float x, float y, float ancho, float alto);
    void actualizarPosicion(Posicion &&posicion);
    void moverHaciaArriba();
    void moverHaciaAbajo();
    void moverHaciaDerecha();
    void moverHaciaIzquierda();
    void detenerse();
};


#endif
