#ifndef LIBRERIACONJUNTOTILES_H
#define LIBRERIACONJUNTOTILES_H
#include "../modelo/LibreriaConjuntoTileParser.h"
#include "Imagen.h"
#include "TileConjunto.h"
#include <vector>

class LibreriaConjuntoTiles {
public:
    LibreriaConjuntoTiles(EntornoGrafico& entorno, 
                                    const LibreriaConjuntoTileParser& parser);
    Imagen* getTile(int id);
    int getColumnas();
    int getAnchoTile();
    int getAltoTile();

private:
    std::vector<TileConjunto> conjuntosTiles;
    int columnas;
    int ancho_tile;
    int alto_tile;
};

#endif
