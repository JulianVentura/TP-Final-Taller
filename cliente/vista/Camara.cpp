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

int Camara::maxX() {
    return abs(contenedor->getAncho() * zoom - marco->getAncho());
}

int Camara::maxY() {
    return abs(contenedor->getAlto() * zoom - marco->getAlto());
}

void Camara::centrar(Renderer* renderer, int ancho_unidad, float radio) {
    zoom = marco->getAncho() / (ancho_unidad * radio);
    zoom = round(zoom * ancho_unidad) / ancho_unidad;
    renderer->escalar(zoom);

    int margen_horizontal = (marco->getAncho() / zoom - objetivo->getAncho()) / 2;
    int margen_vertical = (marco->getAlto() / zoom - objetivo->getAlto()) / 2;
    desplazamientoX = (objetivo->getX() - margen_horizontal) * zoom;
    desplazamientoY = (objetivo->getY() - margen_vertical) * zoom;
    desplazamientoX = acotar(desplazamientoX, 0, maxX());
    desplazamientoY = acotar(desplazamientoY, 0, maxY());
    renderer->desplazar(-desplazamientoX, -desplazamientoY);
}

void Camara::reiniciar(Renderer* renderer) {
    renderer->desplazar(desplazamientoX, desplazamientoY);
    renderer->escalar(1.0f);
}
