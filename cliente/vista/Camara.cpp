#include "Camara.h"

Camara::Camara(IDimensionable& contenedor):
                contenedor(contenedor), marco(&contenedor), objetivo(nullptr) {}

void Camara::setMarco(IDimensionable* marco) {
    this->marco = marco;
}

void Camara::setObjetivo(ITargeteable* objetivo) {
    this->objetivo = objetivo;
}

static int acotar(int x, int inferior, int superior) {
    if (x < inferior) return inferior;
    if (x > superior) return superior;
    return x;
}

int Camara::maxX() {
    return abs(contenedor.getAncho() * zoom - marco->getAncho());
}

int Camara::maxY() {
    return abs(contenedor.getAlto() * zoom - marco->getAlto());
}

void Camara::transformar(int& x, int& y) const {
    x = (x + desplazamientoX) / zoom;
    y = (y + desplazamientoY) / zoom;
}

void Camara::centrar(Renderer* renderer, int ancho_unidad, float radio) {
    if (!objetivo || !marco) return;
    zoom = std::max(marco->getAncho(), marco->getAlto()) / (ancho_unidad * radio);
    zoom = round(zoom * ancho_unidad) / ancho_unidad;
    renderer->escalar(zoom);

    margen_h = (marco->getAncho() / zoom - objetivo->getAncho()) / 2;
    margen_v = (marco->getAlto() / zoom - objetivo->getAlto()) / 2;
    desplazamientoX = (objetivo->getX() - margen_h) * zoom;
    desplazamientoY = (objetivo->getY() - margen_v) * zoom;
    desplazamientoX = acotar(desplazamientoX, 0, maxX());
    desplazamientoY = acotar(desplazamientoY, 0, maxY());
    renderer->desplazar(-desplazamientoX, -desplazamientoY);
}

void Camara::reiniciar(Renderer* renderer) {
    if (!objetivo) return;
    renderer->desplazar(desplazamientoX, desplazamientoY);
    renderer->escalar(1.0f);
}

void Camara::getFrontera(SDL_Rect& frontera) {
    if (!objetivo) return;
    frontera.x = desplazamientoX / zoom;
    frontera.y = desplazamientoY / zoom;
    frontera.w = marco->getAncho() / zoom;
    frontera.h = marco->getAlto() / zoom;
}

void Camara::setContenedor(IDimensionable& contenedor) {
    this->contenedor = contenedor;
}
