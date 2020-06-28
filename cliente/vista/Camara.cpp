#include "Camara.h"

Camara::Camara(IDimensionable* contenedor, IDimensionable* marco): 
                            contenedor(contenedor), marco(marco) {}

void Camara::setObjetivo(ITargeteable& objetivo) {
    this->objetivo = &objetivo;
}

static int acotar(int x, int inferior, int superior) {
    if (x < inferior) return inferior;
    if (x > superior) return superior;
    return x;
}

void Camara::centrar(Renderer* renderer, float zoom) {
    int maxY = abs(contenedor->getAlto() * zoom - marco->getAlto());
    desplazamientoY = acotar(desplazamientoY, 0, maxY);
    /*
    this->zoom = zoom;
    renderer->escalar(zoom);
    int margen_horizontal = (marco->getAncho() / zoom - objetivo->getAncho()) / 2;
    int margen_vertical = (marco->getAlto() / zoom - objetivo->getAlto()) / 2;
    desplazamientoX = (objetivo->getX() - margen_horizontal) * zoom;
    desplazamientoY = (objetivo->getY() - margen_vertical) * zoom;
    int maxX = abs(contenedor->getAncho() * zoom - marco->getAncho());
    int maxY = abs(contenedor->getAlto() * zoom - marco->getAlto());
    desplazamientoX = acotar(desplazamientoX, 0, maxX);
    desplazamientoY = acotar(desplazamientoY, 0, maxY);
    renderer->desplazar(-desplazamientoX, -desplazamientoY);
    */
}

void Camara::reiniciar(Renderer* renderer) {
    renderer->desplazar(desplazamientoX, desplazamientoY);
    renderer->escalar(1.0f);
}
