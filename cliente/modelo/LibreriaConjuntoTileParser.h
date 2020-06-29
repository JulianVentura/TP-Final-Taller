#ifndef LIBRERIACONJUNTOTILEPARSER_H
#define LIBRERIACONJUNTOTILEPARSER_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "InformacionConjuntoTile.h"

class LibreriaConjuntoTileParser {
public:
    LibreriaConjuntoTileParser(nlohmann::json& parser);
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
