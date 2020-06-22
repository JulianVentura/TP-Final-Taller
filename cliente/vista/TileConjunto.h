#ifndef TILECONJUNTO_H
#define TILECONJUNTO_H

#include "Imagen.h"

class TileConjunto {
public:
    TileConjunto(Imagen imagen, unsigned int columnas, unsigned int primer_id, 
        unsigned int cantidad_tiles, unsigned int ancho_tile,
        unsigned int alto_tile);
    bool contieneId(unsigned int id);
    Imagen* imagenPorId(unsigned int id);

private:
    Imagen imagen;
    unsigned int columnas;
    unsigned int primer_id;
    unsigned int cantidad_tiles;
    unsigned int ancho_tile;
    unsigned int alto_tile;
};

#endif