#ifndef MAPAVISTA_H
#define MAPAVISTA_H

#include "IRendereable.h"
#include "IInteractivo.h"
#include "Imagen.h"
#include "Tile.h"
#include "TileConjunto.h"

class MapaVista: public IRendereable, public IInteractivo, 
                                                        public IDimensionable {
public:
    MapaVista() {}; // TODO: provisorio
    // MapaVista &MapaVista::operator=(const MapaVista & otro) = default; // TODO: provisorio
    MapaVista(EntornoGrafico& entorno, 
    std::vector<TileConjunto> conjuntosTiles,
    std::vector<std::vector<int>> capasFondo, int columnas, int filas, int ancho_tile, int alto_tile);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;
    int getColumnas();
    int getFilas();
    int getAnchoTile();
    int getAltoTile();

private:
    std::vector<TileConjunto> conjuntosTiles;
    std::vector<std::vector<int>> capasFondo;
    std::vector<Tile> tiles; // TODO: Provisorio
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
};

#endif
