#include "MapaParser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MapaParser::MapaParser(std::istream& fuente) {
    json parser;
    fuente >> parser;
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "fondo") continue;
        for (auto& capa: grupo["layers"]) {
            this->capasFondo.push_back(capa["data"].get<std::vector<int>>());
        }
    }
    parser["height"].get_to(filas);
    parser["width"].get_to(columnas);
    parser["tileheight"].get_to(alto_tile);
    parser["tilewidth"].get_to(ancho_tile);
}

int MapaParser::getColumnas() { return columnas; }
int MapaParser::getFilas() { return filas; }
int MapaParser::getAnchoTile() { return ancho_tile ;}
int MapaParser::getAltoTile() { return alto_tile; }
std::vector<std::vector<int>> MapaParser::getCapas() {
    return std::move(this->capasFondo);
}