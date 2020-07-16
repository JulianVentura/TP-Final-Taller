#ifndef __POSICION_H__
#define __POSICION_H__
#include "Box.h"
#include <string>
#include "../../common/Serializacion.h"

class Posicion{
    private:
    quadtree::Vector2<float> pos;
    float ancho;
    float alto;
    quadtree::Vector2<float> desplazamiento;
    quadtree::Box<float> areaQueOcupa;
    void actualizarArea();

    Posicion(const quadtree::Vector2<float> &unaPos, 
             const quadtree::Vector2<float> &desp, 
             float ancho, 
             float alto);

    public:
    Posicion();
    Posicion(float x, float y, float ancho, float alto);
    Posicion(const Posicion &otro);
    Posicion(Posicion &&otro);
    Posicion& operator=(Posicion &&otro);
    bool operator==(const Posicion &otro) const;
    void actualizarPosicion(Posicion &&posicion);
    void moverHaciaArriba(float desplazamiento);
    void moverHaciaAbajo(float desplazamiento);
    void moverHaciaDerecha(float desplazamiento);
    void moverHaciaIzquierda(float desplazamiento);
    Posicion mover(const double tiempo) const;
    void detenerse();
    const quadtree::Box<float>& obtenerAreaQueOcupa() const;
    float longitudMaximaDeColision() const;
    float calcularDistancia(const Posicion &otra) const;
    Posicion nuevaPosicionDesplazada(float x, float y) const;
    Posicion perseguir(const Posicion &otraPosicion, 
                       const float factorDesplazamiento, 
                       const double tiempo) const;
    /*
    Devuelve un cuadrado de lado radio.
    */
    const quadtree::Box<float> obtenerAreaCentradaEnPosicion(float radio) const;
    const float obtenerX() const;
    const float obtenerY() const;
    //Serializacion
    struct PosicionEncapsulada serializarPosicion() const;

};

#endif
