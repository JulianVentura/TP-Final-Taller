#ifndef IRENDEREABLE_H
#define IRENDEREABLE_H
#include "Renderer.h"

class IRendereable {
public:
    virtual void render() = 0;
    virtual void actualizar(unsigned int delta_t);
    virtual void setRenderer(Renderer* renderer);
    virtual void setVentana(Ventana* ventana);
protected:
    Renderer* renderer;
    Ventana* ventana;
};

#endif
