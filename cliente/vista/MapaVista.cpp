#include "MapaVista.h"
#include <iostream>
#include <string>
#include "TileConjunto.h"
MapaVista::MapaVista(EntornoGrafico& entorno, MapaParser& parser, LibreriaConjuntoTiles& conjuntosTiles) : 
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
//     for (int i = 0; i < columnas * filas; ++i) {
//         for (auto& capa: capasFondo) {
//             // int id = capa[i];
//             // Imagen* tile = conjuntosTiles.getTile(id);
//             // int x = i % columnas;
//             // int y = (i - x) / columnas;
//             // tile->setPosicion(x * ancho_tile, y * alto_tile);
//             // tile->render();
//         }
//     }
}

void MapaVista::manejarEvento(const SDL_Event& event) {
}
