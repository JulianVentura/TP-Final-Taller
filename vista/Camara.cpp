#include "Camara.h"

void Camara::setObjetivo(ITargeteable& objetivo) {
    this->objetivo = &objetivo;
}

static int acotar(int x, int inferior, int superior) {
    if (x < inferior) return inferior;
    if (x > superior) return superior;
    return x;
}

void Camara::centrar(Renderer* renderer) {
    int margen_horizontal = (marco->getAncho() - objetivo->getAncho()) / 2;
    int margen_vertical = (marco->getAlto() - objetivo->getAlto()) / 2;
    desplazamientoX = objetivo->getX() - margen_horizontal;
    desplazamientoY = objetivo->getY() - margen_vertical;
    // desplazamientoX = acotar(desplazamientoX, 0, contenedor->getAncho() - 2 * margen_horizontal - objetivo->getAncho());
    // desplazamientoY = acotar(desplazamientoY, 0, contenedor->getAlto() - 2 * margen_vertical - objetivo->getAlto());
    desplazamientoX = acotar(desplazamientoX, 0, abs(contenedor->getAncho() - marco->getAncho()));
    desplazamientoY = acotar(desplazamientoY, 0, abs(contenedor->getAlto() - marco->getAlto()));
    renderer->desplazar(-desplazamientoX, -desplazamientoY);
}

void Camara::reiniciar(Renderer* renderer) {
    renderer->desplazar(desplazamientoX, desplazamientoY);
}
