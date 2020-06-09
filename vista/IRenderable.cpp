#include "IRenderable.h"
#include "Ventana.h"

void IRenderable::actualizar() {}

void IRenderable::setRenderer(Renderer* renderer) {
    this->renderer = renderer;
}

void IRenderable::setVentana(Ventana* ventana) {
    this->ventana = ventana;
}
