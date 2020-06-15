#include "MapaVista.h"
#include <string>
const int FILAS = 5;
const int COLUMNAS = 5;
const int ANCHO_TILE = 500;

const bool terreno[FILAS][COLUMNAS] {
    {true, true, true, true, true},
    {true, false, true, false, true},
    {true, false, true, false, true},
    {true, false, false, false, true},
    {true, true, true, true, true}
};

MapaVista::MapaVista(EntornoGrafico& entorno) {
    entorno.agregarRendereable(this);

    const std::string ruta_azul("assets/tile_azul.png");
    const std::string ruta_verde("assets/tile_verde.png");

    imagen_tile_azul = Imagen(entorno, ruta_azul);
    imagen_tile_verde = Imagen(entorno, ruta_verde);

    for (int i = 0; i < COLUMNAS; ++i) {
        for (int j = 0; j < FILAS; ++j) {
            int x = i * ANCHO_TILE;
            int y = j * ANCHO_TILE;
            if (terreno[i][j])
                tiles.push_back(std::move(Tile(entorno, &imagen_tile_azul, x, y)));
            else 
                tiles.push_back(std::move(Tile(entorno, &imagen_tile_verde, x, y)));
        }
    }
    ancho = COLUMNAS * ANCHO_TILE;
    alto = FILAS * ANCHO_TILE;

}

void MapaVista::actualizar(unsigned int delta_t) {
    for (auto& tile: tiles) 
        tile.actualizar(delta_t);
}

void MapaVista::render() {
    for (auto& tile: tiles)
        tile.render();
    imagen_tile_azul.render();
}   

void MapaVista::manejarEvento(const SDL_Event& event) {
}
