#ifndef IRENDERABLE_H
#define IRENDERABLE_H
#include "Renderer.h"

class IRenderable {
public:
    virtual void render() = 0;
    virtual void setRenderer(Renderer* renderer);
    virtual void setVentana(Ventana* ventana);
protected:
    Renderer* renderer;
    Ventana* ventana;
};

#endif
