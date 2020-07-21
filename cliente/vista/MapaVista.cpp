#include "MapaVista.h"
#include "TileConjunto.h"
#include "EntornoMusical.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#define PROB_SONIDO 1

int MapaVista::getColumnas() { return columnas; }
int MapaVista::getFilas() { return filas; }
int MapaVista::getAnchoTile() { return ancho_tile; }
int MapaVista::getAltoTile() { return alto_tile; }

MapaVista::MapaVista(EntornoGrafico& entorno, const MapaParser& parser, 
                    LibreriaConjuntoTiles& conjuntosTiles) {
    entorno.agregarRendereable(this);
    parse(parser, conjuntosTiles);
}
void MapaVista::parse(const MapaParser& parser, 
                                        LibreriaConjuntoTiles& conjuntosTiles) {
    capasFondo.clear();
    rendereables.clear();
    this->conjuntosTiles = (&conjuntosTiles);
    capasFondo = std::move(parser.getCapas()); 
    columnas = parser.getColumnas();
    filas = parser.getFilas();
    ancho_tile = parser.getAnchoTile(); 
    alto_tile = parser.getAltoTile();
    ancho = columnas * ancho_tile;
    alto = filas * alto_tile;
    EntornoMusical::obtenerInstancia()->reproducirSonido("CambioMapa");
}

void MapaVista::actualizar(unsigned int delta_t) {
    for (auto& rendereable: rendereables)
        rendereable.second->actualizar(delta_t);
}

void MapaVista::agregarRendereable(std::string& id, IRendereable* rendereable) {
    if (rendereables.count(id)) return;
    rendereables[id] = rendereable;
}

void MapaVista::render() {
    if (!conjuntosTiles) return;
    int columna_inicial = frontera.x;
    int fila_inicial = frontera.y;
    int columna_final = columna_inicial + frontera.w;
    int fila_final = fila_inicial + frontera.h;
    for (int x = columna_inicial; x <= columna_final; x++) {
        for (int y = fila_inicial; y <= fila_final; y++) {
            unsigned int indice = y * columnas + x;
            for (auto& capa: capasFondo) {
                if (capa.size() <= indice) continue; 
                int id = capa[indice];
                Imagen* tile = conjuntosTiles->getTile(id);
                if (!tile) continue;
                tile->setPosicion(x * ancho_tile, y * alto_tile);
                tile->render();
            }
        }
    }
    for (auto& rendereable: rendereables)
        rendereable.second->render();
    if (std::rand() % 1000 < PROB_SONIDO)
        EntornoMusical::obtenerInstancia()->reproducirSonido("Ambiente1");
}

void MapaVista::setFrontera(SDL_Rect& frontera) {
    this->frontera = frontera;
}
