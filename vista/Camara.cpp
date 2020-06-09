#include "Camara.h"

void Camara::setTarget(ITargeteable& target) {
    this->target = &target;
}

static int acotar(int x, int inferior, int superior) {
    if (x < inferior) return inferior;
    if (x > superior) return superior;
    return x;
}

void Camara::centrar(Renderer* renderer) {
    int centro_x = (contenedor->getAncho() - target->getAncho()) / 2;
    int centro_y = (contenedor->getAlto() - target->getAlto()) / 2;
    xoff = acotar(target->getX() - centro_x, 0, contenedor->getAncho());
    yoff = acotar(target->getY() - centro_y, 0, contenedor->getAlto());
    renderer->desplazar(xoff, yoff);
}

void Camara::reiniciar(Renderer* renderer) {
    renderer->desplazar(-xoff, -yoff);
}
