#include "Obstaculo.h"
#include "Imagen.h"

Obstaculo::Obstaculo(SDL_Rect& dimension, std::vector<int>& guids, 
        LibreriaConjuntoTiles& conjuntoTiles): guids(guids), 
        conjuntoTiles(conjuntoTiles) {
    columna = dimension.x / conjuntoTiles.getAnchoTile();
    fila = dimension.y / conjuntoTiles.getAltoTile();
    ultima_columna = (dimension.x + dimension.w) / conjuntoTiles.getAnchoTile();
    ultima_fila = (dimension.y + dimension.h) / conjuntoTiles.getAltoTile();
    this->ancho = dimension.w;
    this->alto = dimension.h;
    this->x = dimension.x - ancho / 2;
    this->y = dimension.y + alto;
}

void Obstaculo::render() {
    for (int i = columna; i <= ultima_columna; ++i) {
        for (int j = fila; j <= ultima_fila; ++j) {
            int indice = j * conjuntoTiles.getColumnas() + i;
            int id = guids[indice];
            if (id == 0) continue;
            Imagen* tile = conjuntoTiles.getTile(id);
            if (tile == nullptr) continue;
            tile->setPosicion(i * conjuntoTiles.getAnchoTile(), 
                              j * conjuntoTiles.getAltoTile());
            tile->render();
        }
    }
}
