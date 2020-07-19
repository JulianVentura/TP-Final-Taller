#ifndef MAPAVISTA_H
#define MAPAVISTA_H

#include "Camara.h"
#include "IRendereable.h"
#include "Imagen.h"
#include "TileConjunto.h"
#include "LibreriaConjuntoTiles.h"
#include "../modelo/parsers/MapaParser.h"
#include <vector>

class MapaVista: public IRendereable, public IDimensionable {
public:
    MapaVista(EntornoGrafico& entorno, const MapaParser& parser, 
                                        LibreriaConjuntoTiles& conjuntosTiles);
    void parse(const MapaParser& parser, 
                                        LibreriaConjuntoTiles& conjuntosTiles);
    
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void agregarRendereable(std::string& id, IRendereable* rendereable);
    int getColumnas();
    int getFilas();
    int getAnchoTile();
    int getAltoTile();
    void setFrontera(SDL_Rect& frontera);

private:
    LibreriaConjuntoTiles* conjuntosTiles;
    std::vector<std::vector<int>> capasFondo;
    std::unordered_map<std::string, IRendereable*> rendereables;
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
    SDL_Rect frontera = {};
};

#endif
