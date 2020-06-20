#ifndef __POSICION_H__
#define __POSICION_H__
#include "Box.h"
#include <string>

class Posicion{
    private:
    quadtree::Box<float> areaQueOcupa;
    float x;
    float y;
    void actualizarArea();

    public:
    Posicion();
    Posicion(float x, float y);
    //Puede tener sentido hacer una copia, ademas es una clase ligera.
    Posicion(Posicion &otro);
    Posicion(Posicion &&otro);
    Posicion& operator=(Posicion &&otro);
    void PosicionAvanzarHaciaArriba(float desplazamiento);
    void PosicionAvanzarHaciaAbajo(float desplazamiento);
    void PosicionAvanzarHaciaDerecha(float desplazamiento);
    void PosicionAvanzarHaciaIzquierda(float desplazamiento);
    const quadtree::Box<float>& obtenerAreaQueOcupa() const;
    std::string imprimirPosicion();

};

#endif
