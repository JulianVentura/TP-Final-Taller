#include "Obstaculo.h"
#include "Imagen.h"
Obstaculo::Obstaculo(SDL_Rect& dimension, std::vector<int>& guids, 
        LibreriaConjuntoTiles& conjuntosTiles): guids(guids), 
        conjuntosTiles(conjuntosTiles) {
    columna = dimension.x / conjuntosTiles.getAnchoTile();
    fila = dimension.y / conjuntosTiles.getAltoTile();
    ultima_columna = (dimension.x + dimension.w) / conjuntosTiles.getAnchoTile();
    ultima_fila = (dimension.y + dimension.h) / conjuntosTiles.getAltoTile();
    this->ancho = dimension.w;
    this->alto = dimension.h;
    this->x = dimension.x;
    this->y = dimension.y;
}

void Obstaculo::render() {
    for (int i = columna; i <= ultima_columna; ++i) {
        for (int j = fila; j <= ultima_fila; ++j) {
            int indice = j * conjuntosTiles.getColumnas() + i;
            unsigned int id = guids[indice];
            Imagen* tile = conjuntosTiles.getTile(id);
            tile->setPosicion(i * conjuntosTiles.getAnchoTile(), j * conjuntosTiles.getAltoTile());
            tile->render();
        }
    }
}
