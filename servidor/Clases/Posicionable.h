#ifndef __POSICIONABLE_H__
#define __POSICIONABLE_H__
#include "Posicion.h"
#include "Box.h"
class Posicionable{
    protected:
    Posicion posicion;
    float desplazamiento;

    public:
    Posicionable(float x, float y, float ancho, float alto);
    void actualizarPosicion(Posicion &&posicion);
    const quadtree::Box<float>& obtenerAreaQueOcupa();
    const Posicion& obtenerPosicion() const;
    const float obtenerX() const;
    const float obtenerY() const;
    void moverHaciaArriba();
    void moverHaciaAbajo();
    void moverHaciaDerecha();
    void moverHaciaIzquierda();
    void detenerse();
};


#endif
