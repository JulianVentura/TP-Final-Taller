#include "IPosicionable.h"

void IPosicionable::actualizarPosicion(int x, int y) {
    this->x = x;
    this->y = y;
    _esta_actualizado = true;
}

int IPosicionable::getX() const { return x; }
int IPosicionable::getY() const { return y; }
bool IPosicionable::esta_actualizado() const { return _esta_actualizado; }
void IPosicionable::consumirActualizacion() {
    _esta_actualizado = false;
}
