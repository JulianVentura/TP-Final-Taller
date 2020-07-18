#include "MapaVista.h"
#include "TileConjunto.h"
#include <iostream>
#include <string>
#include <utility>

int MapaVista::getColumnas() { return columnas; }
int MapaVista::getFilas() { return filas; }
int MapaVista::getAnchoTile() { return ancho_tile; }
int MapaVista::getAltoTile() { return alto_tile; }

MapaVista::MapaVista(EntornoGrafico& entorno, const MapaParser& parser, 
                    LibreriaConjuntoTiles& conjuntosTiles): 
        conjuntosTiles(&conjuntosTiles),
        capasFondo(std::move(parser.getCapas())), 
        columnas(parser.getColumnas()), 
        filas(parser.getFilas()), 
        ancho_tile(parser.getAnchoTile()), 
        alto_tile(parser.getAltoTile()) {
    entorno.agregarRendereable(this);
    this->ancho = columnas * ancho_tile;
    this->alto = filas * alto_tile;
}

MapaVista& MapaVista::operator=(const MapaVista&& otro) {
    this->conjuntosTiles = otro.conjuntosTiles;
    this->capasFondo = std::move(otro.capasFondo);
    this->columnas = otro.columnas;
    this->filas = otro.filas;
    this->ancho_tile = otro.ancho_tile;
    this->alto_tile = otro.alto_tile;
    this->ancho_tile = otro.ancho_tile;
    this->alto = otro.alto;
    this->ancho = otro.ancho;
    this->renderer = otro.renderer;
    this->ventana = otro.ventana;
    return *this;
}

void MapaVista::render() {
    int columna_inicial = frontera.x;
    int fila_inicial = frontera.y;
    int columna_final = columna_inicial + frontera.w;
    int fila_final = fila_inicial + frontera.h;
    for (int x = columna_inicial; x <= columna_final; x++) {
        for (int y = fila_inicial; y <= fila_final; y++) {
            int indice = y * columnas + x;
            for (auto& capa: capasFondo) {
                int id = capa[indice];
                Imagen* tile = conjuntosTiles->getTile(id);
                if (!tile) continue;
                tile->setPosicion(x * ancho_tile, y * alto_tile);
                tile->render();
            }
        }
    }
}

void MapaVista::setFrontera(SDL_Rect& frontera) {
    this->frontera = frontera;
}
