#ifndef OBSTACULOPARSER_H
#define OBSTACULOPARSER_H
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>

#include "../vista/Obstaculo.h"

class ObstaculoParser {
public:
    ObstaculoParser() = default;
    ObstaculoParser(nlohmann::json& parser, std::unordered_map<std::string, 
             std::vector<int>>& capas, LibreriaConjuntoTiles& conjuntosTiles);
    std::unordered_map<std::string, std::vector<Obstaculo>> 
                                                        getCapasObstaculos();

private:
    std::unordered_map<std::string, std::vector<Obstaculo>> capasObstaculos;
};

#endif
