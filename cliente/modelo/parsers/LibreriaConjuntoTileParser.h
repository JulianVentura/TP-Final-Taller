#ifndef LIBRERIACONJUNTOTILEPARSER_H
#define LIBRERIACONJUNTOTILEPARSER_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../InformacionConjuntoTile.h"

class LibreriaConjuntoTileParser {
public:
    LibreriaConjuntoTileParser() {};
    explicit LibreriaConjuntoTileParser(nlohmann::json& parser);
    void parse(nlohmann::json& parser);
    std::vector<InformacionConjuntoTile> getInformacionLibreria() const;
    int getColumnas() const;
    int getAnchoTile() const;
    int getAltoTile() const;
    
private:
    std::vector<InformacionConjuntoTile> conjuntosTiles;
    int ancho_tile;
    int alto_tile;
    int columnas;
};

#endif
