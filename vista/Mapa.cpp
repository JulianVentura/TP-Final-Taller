#include "Mapa.h"

Mapa::Mapa(EntornoGrafico& entorno) {
    entorno.agregarRenderable(this);
    const std::string path("assets/map.jpg");
    imagen = Imagen(entorno, path);
    imagen.setClip(0, 0, ventana->getAncho(), ventana->getAlto());
    imagen.setAncho(ventana->getAncho() * 2);
    imagen.setAlto(ventana->getAlto() * 2);
}

void Mapa::render() {
    imagen.setPosicion(x, y);
    imagen.render();
    renderer->setColor(0);
    // DEBUG
    renderer->rect(x + 10, y + 10, imagen.getAncho() - 20, 
                                                    imagen.getAlto() - 20);
}

void Mapa::manejarEvento(const SDL_Event& event) {
    
}