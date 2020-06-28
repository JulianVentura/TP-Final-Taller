#ifndef OBSTACULOPARSER_H
#define OBSTACULOPARSER_H
#include <unordered_map>
#include <istream>
#include <vector>
#include "Obstaculo.h"

class ObstaculoParser {
public:
    ObstaculoParser(std::istream& fuente, std::unordered_map<std::string, 
    std::vector<int>>& capas, LibreriaConjuntoTiles& conjuntosTiles);
    std::unordered_map<std::string, std::vector<Obstaculo>> getCapasObstaculos();

private:
    std::unordered_map<std::string, std::vector<Obstaculo>> capasObstaculos;
};

#endif
