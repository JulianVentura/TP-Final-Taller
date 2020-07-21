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
    /* Configura el desplazamiento hacia arriba, con modulo desplazamiento */
    void moverHaciaArriba(float desplazamiento);
    /* Configura el desplazamiento hacia abajo, con modulo desplazamiento */
    void moverHaciaAbajo(float desplazamiento);
    /* Configura el desplazamiento hacia la derecha, con modulo desplazamiento */
    void moverHaciaDerecha(float desplazamiento);
    /* Configura el desplazamiento hacia la izquierda, con modulo desplazamiento */
    void moverHaciaIzquierda(float desplazamiento);
    /* Devuelve una posicion nueva en base al desplazamiento encapsulado dentro de la clase
    la posicion interna no sera pisada. 
    */
    Posicion mover(const double tiempo) const;
    /*
    Detiene el desplazamiento de la Posicion.
    */
    void detenerse();
    const quadtree::Box<float>& obtenerAreaQueOcupa() const;
    float longitudMaximaDeColision() const;
    float calcularDistancia(const Posicion &otra) const;
    Posicion nuevaPosicionDesplazada(float x, float y) const;
    /*
    Devuelve una nueva posicion que minimiza la distancia a otraPosicion en base a un factorDesplazamiento
    La posicion interna no sera afectada.
    */
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
