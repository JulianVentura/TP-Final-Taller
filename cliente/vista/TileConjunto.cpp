#include "TileConjunto.h"

TileConjunto::TileConjunto(Imagen imagen, int columnas, int primer_id, 
        int cantidad_tiles, int ancho_tile, int alto_tile): 
        imagen(std::move(imagen)), columnas(columnas), primer_id(primer_id), 
        cantidad_tiles(cantidad_tiles), ancho_tile(ancho_tile), 
        alto_tile(ancho_tile) {}

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
