#ifndef INFORMACIONCONJUNTOTILE_H
#define INFORMACIONCONJUNTOTILE_H
#include <string>

typedef struct InformacionConjuntoTile {
    std::string ruta;
    int primer_id;
    int cantidad_tiles;
    int ancho_tile;
    int alto_tile;
    int columnas;
    std::string color_transparente;
} InformacionConjuntoTile;

#endif
