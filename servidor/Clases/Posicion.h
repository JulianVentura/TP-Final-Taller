#ifndef __POSICION_H__
#define __POSICION_H__
#include "Box.h"
#include <string>

class Posicion{
    private:
    float x;
    float y;
    float ancho;
    float alto;
    float desplazamientoX;
    float desplazamientoY;
    quadtree::Box<float> areaQueOcupa;
    void actualizarArea();

    public:
    Posicion();
    Posicion(float x, float y, float ancho, float alto);
    Posicion(Posicion &otro) = delete;
    Posicion(Posicion &&otro);
    Posicion& operator=(Posicion &&otro);
    void actualizarPosicion(Posicion &&posicion);
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
    float calcularDistancia(const Posicion &otra) const;
    const float obtenerX() const;
    const float obtenerY() const;

};

#endif
