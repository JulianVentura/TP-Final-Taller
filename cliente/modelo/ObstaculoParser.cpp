#include "ObstaculoParser.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::unordered_map<std::string, std::vector<Obstaculo>> 
                                ObstaculoParser::getCapasObstaculos() const {
    return std::move(this->capasObstaculos);
}

ObstaculoParser::ObstaculoParser(nlohmann::json& parser, 
    std::unordered_map<std::string, std::vector<int>>& capas, 
    LibreriaConjuntoTiles& conjuntosTiles) {
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "frente") continue;
        for (auto& capa: grupo["layers"]) {
            if (capa["type"] != "objectgroup") continue;
            std::string nombre(capa["name"]);
            std::vector<Obstaculo> vector;
            for (auto& objeto: capa["objects"]) {
                SDL_Rect rect = {};
                objeto["x"].get_to(rect.x);
                objeto["y"].get_to(rect.y);
                objeto["width"].get_to(rect.w);
                objeto["height"].get_to(rect.h);
                vector.push_back(std::move(Obstaculo(rect, capas[nombre], 
                                                        conjuntosTiles)));
            }
            capasObstaculos.insert({nombre, std::move(vector)});
        }
    }
}
