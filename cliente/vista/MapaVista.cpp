#include "MapaVista.h"
#include <string>

MapaVista::MapaVista(EntornoGrafico& entorno) {
    entorno.agregarRendereable(this);
    const std::string ruta("assets/map.jpg");
    imagen = Imagen(entorno, ruta);
    imagen.setAncho(imagen.getAncho() * 3);
    imagen.setAlto(imagen.getAlto() * 3);
    ancho = 2 * imagen.getAncho();
    alto = 2 * imagen.getAlto();
}

void MapaVista::actualizar() {
    // imagen.centrarRelativoA(*ventana);   
}

void MapaVista::render() {
    imagen.setPosicion(0, 0);
    imagen.render();
    imagen.setPosicion(0, imagen.getAlto());
    imagen.render();
    imagen.setPosicion(imagen.getAncho(), 0);
    imagen.render();
    imagen.setPosicion(imagen.getAncho(), imagen.getAlto());
    imagen.render();

    // DEBUG
    renderer->setColor(0);
    renderer->rect(x + 10, y + 10, ancho - 20, alto - 20);
}   

void MapaVista::manejarEvento(const SDL_Event& event) {
}
