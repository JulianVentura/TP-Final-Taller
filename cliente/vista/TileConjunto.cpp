#include "TileConjunto.h"
#include <utility>

TileConjunto::TileConjunto(Imagen imagen, InformacionConjuntoTile& info): 
        imagen(std::move(imagen)), 
        columnas(info.columnas), 
        primer_id(info.primer_id), 
        cantidad_tiles(info.cantidad_tiles), 
        ancho_tile(info.ancho_tile), 
        alto_tile(info.ancho_tile) {}

int TileConjunto::getColumnas() {
    return this->columnas;
}
bool TileConjunto::contieneId(int id) {
    return primer_id <= id && (primer_id + cantidad_tiles) > id;
}

Imagen* TileConjunto::imagenPorId(int id) {
    if (!contieneId(id)) return nullptr;
    int id_relativo = id - primer_id;
    int x = id_relativo % columnas;
    int y = (id_relativo - x) / columnas;
    imagen.setMascara(x * ancho_tile, y * alto_tile, ancho_tile, alto_tile);
    return &imagen;
}
