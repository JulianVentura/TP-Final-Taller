#ifndef __POSICIONABLE_H__
#define __POSICIONABLE_H__
#include "Posicion.h"
#include "Rectangulo.h"
class Posicionable{
    protected:
    Posicion posicion;

    public:
    Posicionable();
    void actualizarPosicion(Posicion &&posicion);
    virtual Posicion&& avanzar() = 0;
    Rectangulo& obtenerAreaQueOcupa();
    virtual std::string imprimirPosicion();
};


#endif
