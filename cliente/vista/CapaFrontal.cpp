#include "CapaFrontal.h"
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <utility>

CapaFrontal::CapaFrontal(const CapasParser& parser, 
                                                LibreriaConjuntoTiles& tiles):
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

void CapaFrontal::borrarObstruible(IObstruible* obstruible) {
    obstruibles.erase(std::remove(obstruibles.begin(), obstruibles.end(), 
                                                obstruible), obstruibles.end());
}

void CapaFrontal::setFrontera(SDL_Rect& frontera) {
    this->frontera = frontera; 
}

void CapaFrontal::render() {
    int columna_inicial = frontera.x;
    int fila_inicial = frontera.y;
    int columna_final = columna_inicial + frontera.w;
    int fila_final = fila_inicial + frontera.h;
    for (int x = columna_inicial; x <= columna_final; x++) {
        for (int y = fila_inicial; y <= fila_final; y++) {
            int indice = y * columnas + x;
            for (auto& capa: capas) {
                int id = capa.second[indice];
                if (id == 0) continue;
                Imagen* tile = tiles.getTile(id);
                if (tile == nullptr) continue;
                tile->setPosicion(x * tiles.getAnchoTile(),
                                  y * tiles.getAltoTile());
                tile->render();
            }
        }
    }
    renderearObstruiblesVisibles();
}

void CapaFrontal::renderearObstruiblesVisibles() {
    SDL_Rect frontera_real = { frontera.x * tiles.getAnchoTile(), 
                               frontera.y * tiles.getAltoTile(), 
                               frontera.w * tiles.getAnchoTile() * 2, 
                               frontera.h * tiles.getAltoTile() * 2 };
    std::vector<IObstruible*> obstruibles_visibles;
    for (auto& obstruible: obstruibles) {
        if (!obstruible) continue;
        SDL_Rect obstruible_r;
        SDL_Rect interseccion;
        obstruible->getFrontera(obstruible_r);
        if (SDL_IntersectRect(&frontera_real, &obstruible_r, 
                                        &interseccion) == SDL_FALSE) continue; 
        obstruibles_visibles.push_back(obstruible);
    }
    std::stable_sort(obstruibles_visibles.begin(), obstruibles_visibles.end(), 
                                                        IObstruible::comparar);
    for (auto& obstruible: obstruibles_visibles) {
        if (!obstruible) continue;
        obstruible->render();
    }
}

void CapaFrontal::actualizar(unsigned int delta_t) {
    for (auto& obstruible: obstruibles)
        obstruible->actualizar(delta_t);
}
