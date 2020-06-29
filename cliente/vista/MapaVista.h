#ifndef MAPAVISTA_H
#define MAPAVISTA_H

#include "IRendereable.h"
#include "IInteractivo.h"
#include "Imagen.h"
#include "TileConjunto.h"
#include "../modelo/MapaParser.h"
#include "LibreriaConjuntoTiles.h"

class MapaVista: public IRendereable, public IDimensionable {
public:
    MapaVista(EntornoGrafico& entorno, MapaParser& parser, 
                                        LibreriaConjuntoTiles& conjuntosTiles);
    void render() override;
    int getColumnas();
    int getFilas();
    int getAnchoTile();
    int getAltoTile();

private:
    LibreriaConjuntoTiles& conjuntosTiles;
    std::vector<std::vector<int>> capasFondo;
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
};

#endif
