#ifndef CAMARA_H
#define CAMARA_H

#include "IDimensionable.h"
#include "ITargeteable.h"
#include "Renderer.h"

class Camara {
public:
    Camara() = default;
    explicit Camara(IDimensionable* contenedor, IDimensionable* marco): 
                contenedor(contenedor), marco(marco) {}
    void setObjetivo(ITargeteable& objetivo);
    void centrar(Renderer* renderer);
    void reiniciar(Renderer* renderer);

private:
    IDimensionable* contenedor;
    IDimensionable* marco;
    ITargeteable* objetivo;
    int desplazamientoX = 0;
    int desplazamientoY = 0;
};
#endif
