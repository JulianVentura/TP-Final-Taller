#include "CapasParser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unordered_map<std::string, std::vector<int>> CapasParser::getCapas() {
    return std::move(this->capas);
}

std::vector<std::string> CapasParser::getCapasOrdenadas() {
    return std::move(this->capasOrdenadas);
}

CapasParser::CapasParser(std::istream& fuente) {
    json parser;
    fuente >> parser;    
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "frente") continue;
        for (auto& capa: grupo["layers"]) {
            if (capa["type"] == "tilelayer") {
                capas.insert({capa["name"], capa["data"].get<std::vector<int>>()});
                capasOrdenadas.push_back(capa["name"]);
            }
        }
    }
}