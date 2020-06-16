#include "IRendereable.h"
#include "Ventana.h"

void IRendereable::actualizar(unsigned int delta_t) {}

void IRendereable::setRenderer(Renderer* renderer) {
    this->renderer = renderer;
}

void IRendereable::setVentana(Ventana* ventana) {
    this->ventana = ventana;
}
