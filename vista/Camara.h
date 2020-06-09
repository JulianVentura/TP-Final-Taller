#ifndef CAMARA_H
#define CAMARA_H

#include "IDimensionable.h"
#include "ITargeteable.h"
#include "Renderer.h"

class Camara {
public:
    Camara() = default;
    Camara(IDimensionable* contenedor): contenedor(contenedor){}
    void setTarget(ITargeteable& target);
    void centrar(Renderer* renderer);
    void reiniciar(Renderer* renderer);

private:
    IDimensionable* contenedor;
    ITargeteable* target;
    int xoff = 0;
    int yoff = 0;
};

#endif