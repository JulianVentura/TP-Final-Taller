#ifndef TILECONJUNTO_H
#define TILECONJUNTO_H
#include "../modelo/InformacionConjuntoTile.h"

#include "Imagen.h"

class TileConjunto {
public:
    TileConjunto(Imagen imagen, InformacionConjuntoTile& info);
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