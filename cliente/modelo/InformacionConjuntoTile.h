#ifndef INFORMACIONCONJUNTOTILE_H
#define INFORMACIONCONJUNTOTILE_H
#include <string>

typedef struct InformacionConjuntoTile {
    std::string ruta;
    int primer_id = 0;
    int cantidad_tiles = 0;
    int ancho_tile = 0;
    int alto_tile = 0;
    int columnas = 0;
    std::string color_transparente;
} InformacionConjuntoTile;

#endif
