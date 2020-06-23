#include "MapaVista.h"
#include <iostream>
#include <string>
#include "TileConjunto.h"
int MapaVista::getColumnas() { return columnas; }
int MapaVista::getFilas() { return filas; }
int MapaVista::getAnchoTile() { return ancho_tile; }
int MapaVista::getAltoTile() { return alto_tile; }

// TODO: se está pasando todo por copia
MapaVista::MapaVista(EntornoGrafico& entorno, 
std::vector<TileConjunto> conjuntosTiles,
std::vector<std::vector<int>> capasFondo, int columnas, int filas, int ancho_tile, int alto_tile) : conjuntosTiles(conjuntosTiles),
capasFondo(capasFondo), columnas(columnas), filas(filas), ancho_tile(ancho_tile), alto_tile(alto_tile) {
    entorno.agregarRendereable(this);
    this->ancho = columnas * ancho_tile;
    this->alto = filas * alto_tile;
}

void MapaVista::actualizar(unsigned int delta_t) {
}

void MapaVista::render() {
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFondo) {
            int id = capa[i];
            for (auto& conjunto_tile: conjuntosTiles) {
                if (id == 0) break;
                if (!conjunto_tile.contieneId(id)) continue;
                Imagen* tile = conjunto_tile.imagenPorId(id);
                int x = i % columnas;
                int y = (i - x) / columnas;
                tile->setPosicion(x * ancho_tile, y * alto_tile);
                tile->render();
           }
        }
    }

}

void MapaVista::manejarEvento(const SDL_Event& event) {
}
