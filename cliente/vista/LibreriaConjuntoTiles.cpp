#include "LibreriaConjuntoTiles.h"

int LibreriaConjuntoTiles::getColumnas() { return columnas; }
int LibreriaConjuntoTiles::getAnchoTile() { return ancho_tile ;}
int LibreriaConjuntoTiles::getAltoTile() { return alto_tile; }

LibreriaConjuntoTiles::LibreriaConjuntoTiles(EntornoGrafico& entorno, LibreriaConjuntoTileParser& parser) {
    entorno.agregarRendereable(this);
    columnas = parser.getColumnas();
    ancho_tile = parser.getAnchoTile();
    alto_tile = parser.getAltoTile();
    std::vector<InformacionConjuntoTile> info_tiles = std::move(parser.getInformacionLibreria());
    for (auto& info_tile: info_tiles) {
        Imagen imagen;
            
        if (info_tile.color_transparente != "") {
            SDL_Color color = renderer->colorDesdeHexa(info_tile.color_transparente);
            imagen = Imagen(entorno, "assets/" + info_tile.ruta, &color);
        } else {
            imagen = Imagen(entorno, "assets/" + info_tile.ruta);
        }
        conjuntosTiles.push_back(std::move(TileConjunto(std::move(imagen), 
            columnas, info_tile.primer_id, info_tile.cantidad_tiles, 
            ancho_tile, alto_tile)));
    }

    // for (auto& info_tile: info_tiles) {
    //     for (int i = info_tile.primer_id; i < info_tile.primer_id + info_tile.cantidad_tiles; ++i) {
    //         Imagen* tile = this->getTile(i);
    //         // printf("%d %d\n", info_tile.primer_id, tile->getAlto());
    //     }
    // }
    // exit(0);
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
