#ifndef MAPAPARSER_H
#define MAPAPARSER_H
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class MapaParser {
public:
    explicit MapaParser(nlohmann::json& parser);
    void parse(nlohmann::json& parser);
    int getColumnas() const;
    int getFilas() const;
    int getAnchoTile() const;
    int getAltoTile() const;
    std::vector<std::vector<int>> getCapas() const;

private:
    std::vector<std::vector<int>> capasFondo;
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
};

#endif
