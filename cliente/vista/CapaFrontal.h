#ifndef CAPAFRONTAL_H
#define CAPAFRONTAL_H

#include "IRendereable.h" 
#include "LibreriaConjuntoTiles.h"
#include "../modelo/parsers/ObstaculoParser.h"
#include "../modelo/parsers/CapasParser.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>


class CapaFrontal: public IRendereable {
public:
    CapaFrontal(const CapasParser& parser, LibreriaConjuntoTiles& tiles);
    void parse(const CapasParser& parser, LibreriaConjuntoTiles& tiles);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void agregarObstruible(const std::string& id, IObstruible* obstruible);
    void borrarObstruible(const std::string& id);
    void setFrontera(SDL_Rect& frontera);

private:
    void renderearObstruiblesVisibles();
    std::vector<IObstruible*> obstruiblesFijos;
    std::unordered_map<std::string, IObstruible*> obstruibles;
    std::unordered_map<std::string, std::vector<int>> capas;
    std::unordered_map<std::string, std::vector<Obstaculo>> capasObstaculos;
    LibreriaConjuntoTiles* tiles;
    SDL_Rect frontera;
    std::mutex m;
    int columnas;
    int filas;
};

#endif
