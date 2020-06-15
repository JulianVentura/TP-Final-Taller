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

    const std::string ruta("assets/map.jpg");
    imagen = Imagen(entorno, ruta);
    
    // imagen.setAncho(imagen.getAncho() * 3);
    // imagen.setAlto(imagen.getAlto() * 3);
    // ancho = 2 * imagen.getAncho();
    // alto = 2 * imagen.getAlto();

    ancho = COLUMNAS * ANCHO_TILE;
    alto = FILAS * ANCHO_TILE;

}

void MapaVista::actualizar(unsigned int delta_t) {
    // imagen.centrarRelativoA(*ventana);   
}

void MapaVista::render() {
    // imagen.setPosicion(0, 0);
    // imagen.render();
    // imagen.setPosicion(0, imagen.getAlto());
    // imagen.render();
    // imagen.setPosicion(imagen.getAncho(), 0);
    // imagen.render();
    // imagen.setPosicion(imagen.getAncho(), imagen.getAlto());
    // imagen.render();

    for (int i = 0; i < COLUMNAS; ++i) {
        for (int j = 0; j < FILAS; ++j) {
            if (terreno[i][j])
                renderer->setColor(51);
            else 
                renderer->setColor(51, 0, 51);
            renderer->rectSolido(i * ANCHO_TILE, j * ANCHO_TILE, ANCHO_TILE, ANCHO_TILE);
        }
    }
}   

void MapaVista::manejarEvento(const SDL_Event& event) {
}
