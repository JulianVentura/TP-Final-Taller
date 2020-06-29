#include "MapaVista.h"
#include <iostream>
#include <string>
#include "TileConjunto.h"

int MapaVista::getColumnas() { return columnas; }
int MapaVista::getFilas() { return filas; }
int MapaVista::getAnchoTile() { return ancho_tile; }
int MapaVista::getAltoTile() { return alto_tile; }

MapaVista::MapaVista(EntornoGrafico& entorno, MapaParser& parser, 
                                        LibreriaConjuntoTiles& conjuntosTiles): 
        conjuntosTiles(conjuntosTiles),
        capasFondo(std::move(parser.getCapas())), 
        columnas(parser.getColumnas()), 
        filas(parser.getFilas()), 
        ancho_tile(parser.getAnchoTile()), 
        alto_tile(parser.getAltoTile()) {
    entorno.agregarRendereable(this);
    this->ancho = columnas * ancho_tile;
    this->alto = filas * alto_tile;
}

void MapaVista::render() {
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFondo) {
            int id = capa[i];
            Imagen* tile = conjuntosTiles.getTile(id);
            if (!tile) continue;
            int x = i % columnas;
            int y = (i - x) / columnas;
            tile->setPosicion(x * ancho_tile, y * alto_tile);
            tile->render();
        }
    }
}
