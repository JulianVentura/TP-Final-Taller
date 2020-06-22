#include "TileConjunto.h"

TileConjunto::TileConjunto(Imagen imagen, unsigned int columnas, unsigned int 
        primer_id, unsigned int cantidad_tiles, unsigned int ancho_tile,
        unsigned int alto_tile): 
        imagen(imagen), columnas(columnas), primer_id(primer_id), 
        cantidad_tiles(cantidad_tiles), ancho_tile(ancho_tile), 
        alto_tile(ancho_tile) {}

bool TileConjunto::contieneId(unsigned int id) {
    return primer_id <= id && (primer_id + cantidad_tiles) > id;
}

Imagen* TileConjunto::imagenPorId(unsigned int id) {
    if (!contieneId(id)) return NULL;
    unsigned int id_relativo = id - primer_id;
    int x = id_relativo % columnas;
    int y = (id_relativo - x) / columnas;
    imagen.setMascara(x * ancho_tile, y * alto_tile, ancho_tile, alto_tile);
    return &imagen;
}
