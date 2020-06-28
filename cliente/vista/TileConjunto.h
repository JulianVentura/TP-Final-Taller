#ifndef TILECONJUNTO_H
#define TILECONJUNTO_H

#include "Imagen.h"

class TileConjunto {
public:
    TileConjunto(Imagen imagen, int columnas, int primer_id, int cantidad_tiles, 
        int ancho_tile, int alto_tile);
    int getColumnas();
    bool contieneId(int id);
    Imagen* imagenPorId(int id);

private:
    Imagen imagen;
    int columnas;
    int primer_id;
    int cantidad_tiles;
    int ancho_tile;
    int alto_tile;
};

#endif