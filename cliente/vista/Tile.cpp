#include "Tile.h"

Tile::Tile(EntornoGrafico& entorno, Imagen* imagen, int x, int y):
        imagen(imagen), x(x), y(y) {
    entorno.agregarRendereable(this);
    this->imagen->setAncho(ANCHO_TILE);
    this->imagen->setAlto(ANCHO_TILE);
}

void Tile::setMascara(int x, int y, int ancho, int alto) {
    mascara = {x, y, ancho, alto};
}

void Tile::actualizar(unsigned int delta_t) {
}

void Tile::render() {
    imagen->setPosicion(x, y);
    imagen->setMascara(mascara.x, mascara.y, mascara.w, mascara.h);
    imagen->render();
}
