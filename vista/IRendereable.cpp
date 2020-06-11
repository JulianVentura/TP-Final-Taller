#include "IRendereable.h"
#include "Ventana.h"

void IRendereable::actualizar() {}

void IRendereable::setRenderer(Renderer* renderer) {
    this->renderer = renderer;
}

void IRendereable::setVentana(Ventana* ventana) {
    this->ventana = ventana;
}
