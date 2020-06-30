#include "CapasParser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int CapasParser::getColumnas() { return columnas; }
int CapasParser::getFilas() { return filas; }

std::unordered_map<std::string, std::vector<int>> CapasParser::getCapas() {
    return std::move(this->capas);
}

std::unordered_map<std::string, std::vector<Obstaculo>> 
        CapasParser::getCapasObstaculos() {
    return std::move(obstaculoParser.getCapasObstaculos());
}

std::vector<std::string> CapasParser::getCapasOrdenadas() {
    return std::move(this->capasOrdenadas);
}

CapasParser::CapasParser(nlohmann::json& parser, LibreriaConjuntoTiles* tiles) {
    parser["width"].get_to(columnas);
    parser["height"].get_to(filas);
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "frente") continue;
        for (auto& capa: grupo["layers"]) {
            if (capa["type"] != "tilelayer") continue;
            capas.insert({capa["name"], capa["data"].get<std::vector<int>>()});
            capasOrdenadas.push_back(capa["name"]);
        }
    }
    obstaculoParser = ObstaculoParser(parser, capas, *tiles);
}
