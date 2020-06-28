#ifndef MAPAPARSER_H
#define MAPAPARSER_H
#include <vector>
#include <fstream>

class MapaParser {
public:
    MapaParser(std::istream& fuente);
    int getColumnas();
    int getFilas();
    int getAnchoTile();
    int getAltoTile();
    std::vector<std::vector<int>> getCapas();

private:
    std::vector<std::vector<int>> capasFondo;
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
};

#endif
