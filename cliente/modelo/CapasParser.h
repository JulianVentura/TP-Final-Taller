#ifndef CAPASPARSER_H
#define CAPASPARSER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "../vista/LibreriaConjuntoTiles.h"
#include "ObstaculoParser.h"

class CapasParser {
public:
    CapasParser(nlohmann::json& parser, LibreriaConjuntoTiles& tiles);
    std::unordered_map<std::string, std::vector<int>> getCapas() const;
    std::vector<std::string> getCapasOrdenadas() const;
    std::unordered_map<std::string, std::vector<Obstaculo>> 
                                                    getCapasObstaculos() const;
    int getColumnas() const;
    int getFilas() const;

private:
    ObstaculoParser obstaculoParser;
    std::unordered_map<std::string, std::vector<int>> capas;
    std::vector<std::string> capasOrdenadas;
    int columnas;
    int filas;
};
#endif
