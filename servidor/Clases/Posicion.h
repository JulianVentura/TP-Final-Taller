#ifndef __POSICION_H__
#define __POSICION_H__
#include "Rectangulo.h"
#include <string>

class Posicion{
    private:
    Rectangulo areaQueOcupa;
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
    Rectangulo& obtenerAreaQueOcupa();
    std::string imprimirPosicion();

};

#endif
