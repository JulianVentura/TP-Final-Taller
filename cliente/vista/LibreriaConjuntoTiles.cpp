#include "LibreriaConjuntoTiles.h"
#include <iostream>

int LibreriaConjuntoTiles::getColumnas() { return columnas; }
int LibreriaConjuntoTiles::getAnchoTile() { return ancho_tile ;}
int LibreriaConjuntoTiles::getAltoTile() { return alto_tile; }

LibreriaConjuntoTiles::LibreriaConjuntoTiles(EntornoGrafico& entorno,
                                        LibreriaConjuntoTileParser& parser) {
    entorno.agregarRendereable(this);
    columnas = parser.getColumnas();
    ancho_tile = parser.getAnchoTile();
    alto_tile = parser.getAltoTile();
    std::vector<InformacionConjuntoTile> info_tiles = 
                                    std::move(parser.getInformacionLibreria());
    for (auto& info_tile: info_tiles) {
        Imagen imagen;
        if (info_tile.color_transparente != "") {
            SDL_Color color = renderer->colorDesdeHexa(
                                                info_tile.color_transparente);
            imagen = std::move(Imagen(entorno, "assets/" + info_tile.ruta, 
                                                                    &color));
        } else {
            imagen = std::move(Imagen(entorno, "assets/" + info_tile.ruta));
        }
        conjuntosTiles.push_back(std::move(TileConjunto(std::move(imagen), 
            info_tile.columnas, info_tile.primer_id, info_tile.cantidad_tiles, 
            info_tile.ancho_tile, info_tile.alto_tile)));
    } 
}

Imagen* LibreriaConjuntoTiles::getTile(int id) {
    Imagen* tile = nullptr;
    for (auto& conjunto_tile: this->conjuntosTiles) {
        if (id == 0) break;
        if (!conjunto_tile.contieneId(id)) continue;
        tile = conjunto_tile.imagenPorId(id);
    }
    return tile;
}
