#ifndef LIBRERIACONJUNTOTILES_H
#define LIBRERIACONJUNTOTILES_H
#include "IRendereable.h" // TODO: provisorio
#include "LibreriaConjuntoTileParser.h"
#include "Imagen.h"
#include "TileConjunto.h"

                                // TODO: provisorio
class LibreriaConjuntoTiles : public IRendereable {
public:
    LibreriaConjuntoTiles() {} // TODO: provisorio
    LibreriaConjuntoTiles(EntornoGrafico& entorno, LibreriaConjuntoTileParser& parser);
    Imagen* getTile(int id);
    void render() {} // TODO: provisorio
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
