#ifndef __POSICIONABLE_H__
#define __POSICIONABLE_H__
#include "Posicion.h"
#include "Box.h"
class Posicionable{
    protected:
    Posicion posicion;

    public:
    Posicionable();
    void actualizarPosicion(Posicion &&posicion);
    virtual Posicion&& avanzar() = 0;
    const quadtree::Box<float>& obtenerAreaQueOcupa();
    const Posicion& obtenerPosicion() const;
    virtual std::string imprimirPosicion();
    const float obtenerX() const;
    const float obtenerY() const;
};


#endif
