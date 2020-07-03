#include "IPosicionable.h"

void IPosicionable::actualizarPosicion(int x, int y) {
    this->x = x;
    this->y = y;
    esta_actualizado = true;
}
