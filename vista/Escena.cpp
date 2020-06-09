#include "Escena.h"

Escena::Escena(EntornoGrafico& entorno): personaje(entorno), mapa(entorno) {
    entorno.agregarRenderable(this);
    camara = Camara(ventana);
    camara.setTarget(personaje);
}

void Escena::render() {
    camara.centrar(renderer);
    mapa.render();
    personaje.render();
    camara.reiniciar(renderer);
    // DEBUG
    renderer->setColor(51);
    renderer->rectSolido(ventana->getAncho() / 2, ventana->getAlto() / 2, 
                                                                10, 10);
}

void Escena::manejarEvento(const SDL_Event& event) {
    mapa.manejarEvento(event);
    personaje.manejarEvento(event);
}

void Escena::actualizar() {
    personaje.actualizar();
}