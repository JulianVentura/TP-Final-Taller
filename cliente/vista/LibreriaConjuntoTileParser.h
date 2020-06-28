#ifndef LIBRERIACONJUNTOTILEPARSER_H
#define LIBRERIACONJUNTOTILEPARSER_H
#include <string>
#include <vector>
#include <istream>

typedef struct InformacionConjuntoTile {
    std::string ruta;
    int primer_id;
    int cantidad_tiles;
    std::string color_transparente;
} InformacionConjuntoTile;

class LibreriaConjuntoTileParser {
public:
    LibreriaConjuntoTileParser(std::istream& fuente);
    std::vector<InformacionConjuntoTile> getInformacionLibreria();
    int getColumnas();
    int getAnchoTile();
    int getAltoTile();
    
private:
    std::vector<InformacionConjuntoTile> conjuntosTiles;
    int ancho_tile;
    int alto_tile;
    int columnas;
};

#endif
