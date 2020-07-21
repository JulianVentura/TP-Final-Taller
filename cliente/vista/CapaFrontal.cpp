#include "CapaFrontal.h"
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <mutex>
#include <utility>

CapaFrontal::CapaFrontal(const CapasParser& parser, 
                                                LibreriaConjuntoTiles& tiles) {
    parse(parser, tiles);
}

void CapaFrontal::parse(const CapasParser& parser, 
                                                LibreriaConjuntoTiles& tiles) {
    capas.clear();
    capasObstaculos.clear();
    obstruibles.clear();
    obstruiblesFijos.clear();
    capas = std::move(parser.getCapas());
    this->tiles = &tiles;
    columnas = parser.getColumnas(); 
    filas = parser.getFilas();
    capasObstaculos = std::move(parser.getCapasObstaculos());
    for (const auto& nombreCapa: parser.getCapasOrdenadas()) {
        if (capasObstaculos.count(nombreCapa) < 0) continue;
        for (auto& obstaculo: capasObstaculos[nombreCapa])
            obstruiblesFijos.push_back(&obstaculo);
    }
}

void CapaFrontal::agregarObstruible(const std::string& id, IObstruible* obstruible) {
    std::lock_guard<std::mutex> l(m);
    if (obstruibles.count(id)) return;
    obstruibles.insert({ id, obstruible });
}

void CapaFrontal::borrarObstruible(const std::string& id) {
    std::lock_guard<std::mutex> l(m);
    obstruibles.erase(id);
}

void CapaFrontal::setFrontera(SDL_Rect& frontera) {
    this->frontera = frontera; 
}

void CapaFrontal::render() {
    int columna_inicial = std::max(frontera.x, 0);
    int fila_inicial = std::max(frontera.y, 0);
    int columna_final = std::min(columna_inicial + frontera.w, columnas);
    int fila_final = std::min(fila_inicial + frontera.h, filas);
    for (int x = columna_inicial; x <= columna_final; x++) {
        for (int y = fila_inicial; y <= fila_final; y++) {
            int indice = y * columnas + x;
            for (auto& capa: capas) {
                int id = capa.second[indice];
                if (id == 0) continue;
                Imagen* tile = tiles->getTile(id);
                if (!tile) continue;
                tile->setPosicion(x * tiles->getAnchoTile(),
                                  y * tiles->getAltoTile());
                tile->render();
            }
        }
    }
    renderearObstruiblesVisibles();
}

void CapaFrontal::renderearObstruiblesVisibles() {
    SDL_Rect frontera_real = { frontera.x * tiles->getAnchoTile(), 
                               frontera.y * tiles->getAltoTile(), 
                               frontera.w * tiles->getAnchoTile(), 
                               frontera.h * tiles->getAltoTile() };
    
    std::vector<IObstruible*> obstruibles_visibles;
    for (auto& obstruible: obstruibles) {
        if (!obstruible.second) continue;
        SDL_Rect obstruible_r;
        SDL_Rect interseccion;
        obstruible.second->getFrontera(obstruible_r);
        if (SDL_IntersectRect(&frontera_real, &obstruible_r, 
                                        &interseccion) == SDL_FALSE) continue; 
        obstruibles_visibles.push_back(obstruible.second);
    }
    for (auto& obstruible: obstruiblesFijos) {
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
    for (auto& obstruible: obstruiblesFijos) {
        if (!obstruible) continue;
        obstruible->actualizar(delta_t);
    }
    for (auto& obstruible: obstruibles) {
        if (!obstruible.second) continue;
        obstruible.second->actualizar(delta_t);
    }
}
