#include "IObstruible.h"

int IObstruible::getX() {
    return x - ancho / 2;
}

int IObstruible::getY() {
    return  y - alto;
}

bool IObstruible::comparar(IObstruible* obstruible,  IObstruible* otro) {
    return otro->getY() + otro->getAlto() > obstruible->getY() 
                                                        + obstruible->getAlto();
}

void IObstruible::getFrontera(SDL_Rect& frontera) {
    frontera = {x, y, ancho, alto};
}
