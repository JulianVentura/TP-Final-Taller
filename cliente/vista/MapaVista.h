#ifndef MAPAVISTA_H
#define MAPAVISTA_H

#include "Camara.h"
#include "IRendereable.h"
#include "Imagen.h"
#include "TileConjunto.h"
#include "LibreriaConjuntoTiles.h"
#include "../modelo/MapaParser.h"
#include <vector>

class MapaVista: public IRendereable, public IDimensionable {
public:
    MapaVista(EntornoGrafico& entorno, const MapaParser& parser, 
                                        LibreriaConjuntoTiles& conjuntosTiles);
    void render() override;
    int getColumnas();
    int getFilas();
    int getAnchoTile();
    int getAltoTile();
    void setFrontera(SDL_Rect& frontera);

private:
    LibreriaConjuntoTiles& conjuntosTiles;
    std::vector<std::vector<int>> capasFondo;
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
    SDL_Rect frontera = {};
};

#endif
