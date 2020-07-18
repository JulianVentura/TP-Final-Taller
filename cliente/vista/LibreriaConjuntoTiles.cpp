#include "LibreriaConjuntoTiles.h"
#include "Colores.h"
#include <iostream>
#include <utility>

#define RUTA_ASSETS "assets/"

int LibreriaConjuntoTiles::getColumnas() { return columnas; }
int LibreriaConjuntoTiles::getAnchoTile() { return ancho_tile ;}
int LibreriaConjuntoTiles::getAltoTile() { return alto_tile; }

LibreriaConjuntoTiles::LibreriaConjuntoTiles(EntornoGrafico& entorno,
                                    const LibreriaConjuntoTileParser& parser) {
    parse(entorno, parser);
}

void LibreriaConjuntoTiles::parse(EntornoGrafico& entorno,
                                    const LibreriaConjuntoTileParser& parser) {
    conjuntosTiles.clear();
    columnas = parser.getColumnas();
    ancho_tile = parser.getAnchoTile();
    alto_tile = parser.getAltoTile();

    std::vector<InformacionConjuntoTile> info_tiles = 
                                    std::move(parser.getInformacionLibreria());
    
    for (auto& info_tile: info_tiles) {
        SDL_Color color = {};
        SDL_Color *color_ptr = nullptr;
        if (info_tile.color_transparente != "") {
            color = Colores::colorDesdeHexa(info_tile.color_transparente);
            color_ptr = &color;
        }
        Imagen img = Imagen(entorno, RUTA_ASSETS + info_tile.ruta, color_ptr);
        TileConjunto tile_conjunto = TileConjunto(/*std::move*/(img), info_tile);
        conjuntosTiles.push_back(/*std::move*/(tile_conjunto));
    }
}
Imagen* LibreriaConjuntoTiles::getTile(int id) {
    Imagen* tile = nullptr;
    for (auto& conjunto_tile: conjuntosTiles) {
        if (id == 0) break;
        if (!conjunto_tile.contieneId(id)) continue;
        tile = conjunto_tile.imagenPorId(id);
    }
    return tile;
}
