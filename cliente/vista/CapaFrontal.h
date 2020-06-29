#ifndef CAPAFRONTAL_H
#define CAPAFRONTAL_H

#include "IRendereable.h" 
#include "LibreriaConjuntoTiles.h"
#include "../modelo/ObstaculoParser.h"
#include "../modelo/CapasParser.h"
#include <string>
#include <unordered_map>
#include <vector>


class CapaFrontal: public IRendereable {
public:
    CapaFrontal() {};
    CapaFrontal(CapasParser& parser, LibreriaConjuntoTiles* tiles);
    void render() override;
    void actualizar(unsigned int delta_t) override;

    void agregarObstruible(IObstruible* obstruible);

private:
    std::vector<IObstruible*> obstruibles;
    std::unordered_map<std::string, std::vector<int>> capas;
    std::unordered_map<std::string, std::vector<Obstaculo>> capasObstaculos;
    LibreriaConjuntoTiles* tiles;
    int columnas;
    int filas;
};

#endif
