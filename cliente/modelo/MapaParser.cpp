#include "MapaParser.h"
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;

MapaParser::MapaParser(nlohmann::json& parser) {
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

int MapaParser::getColumnas() const { return columnas; }
int MapaParser::getFilas() const { return filas; }
int MapaParser::getAnchoTile() const { return ancho_tile ;}
int MapaParser::getAltoTile() const { return alto_tile; }
std::vector<std::vector<int>> MapaParser::getCapas() const {
    return std::move(this->capasFondo);
}
