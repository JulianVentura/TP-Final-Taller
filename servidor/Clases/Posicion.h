#ifndef __POSICION_H__
#define __POSICION_H__
#include "Box.h"
#include <string>

class Posicion{
    private:
    quadtree::Box<float> areaQueOcupa;
    float x;
    float y;
    float desplazamientoX;
    float desplazamientoY;
    void actualizarArea();

    public:
    Posicion();
    Posicion(float x, float y);
    //Puede tener sentido hacer una copia, ademas es una clase ligera.
    //Posicion(Posicion &otro);
    Posicion(Posicion &&otro);
    Posicion& operator=(Posicion &&otro);
    void moverHaciaArriba(float desplazamiento);
    void moverHaciaAbajo(float desplazamiento);
    void moverHaciaDerecha(float desplazamiento);
    void moverHaciaIzquierda(float desplazamiento);
    Posicion mover();
    void detenerse();
    const quadtree::Box<float>& obtenerAreaQueOcupa() const;
    float longitudMaximaDeColision() const;
    Posicion nuevaPosicionDesplazada(float x, float y) const;
    std::string imprimirPosicion();
    const float obtenerX() const;
    const float obtenerY() const;

};

#endif
