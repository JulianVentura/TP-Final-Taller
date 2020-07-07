#include "CapaFrontal.h"
#include <algorithm>
#include <utility>

CapaFrontal::CapaFrontal(CapasParser& parser, LibreriaConjuntoTiles* tiles):
        capas(std::move(parser.getCapas())),
        tiles(tiles), 
        columnas(parser.getColumnas()), 
        filas(parser.getFilas()) {
    capasObstaculos = std::move(parser.getCapasObstaculos());
    for (const auto& nombreCapa: parser.getCapasOrdenadas()) {
        if (capasObstaculos.count(nombreCapa) < 0) continue;
        for (auto& obstaculo: capasObstaculos[nombreCapa])
            obstruibles.push_back(&obstaculo);
    }
}

void CapaFrontal::agregarObstruible(IObstruible* obstruible) {
    this->obstruibles.push_back(obstruible);
}

static bool obstruible_cmp(IObstruible* obstruible,  IObstruible* otro) {
    return otro->getY() > obstruible->getY();
}

void CapaFrontal::render() {
    // TODO: se debería acotar a lo visible
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capas) {
            int id = capa.second[i];
            if (id == 0) continue;
            int x = i % columnas;
            int y = (i - x) / columnas;
            Imagen* tile = tiles->getTile(id);
            if (tile == nullptr) continue;
            x *= tiles->getAnchoTile();
            y *= tiles->getAltoTile();
            tile->setPosicion(x, y);
            tile->render();
        }
    }

    // TODO: se debería acotar a lo visible
    std::stable_sort(obstruibles.begin(), obstruibles.end(), obstruible_cmp);

    for (auto& obstruible: obstruibles)
        obstruible->render();
}

void CapaFrontal::actualizar(unsigned int delta_t) {
    for (auto& obstruible: obstruibles)
        obstruible->actualizar(delta_t);
}
