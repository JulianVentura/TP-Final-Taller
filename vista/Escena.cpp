#include "Escena.h"

Escena::Escena(EntornoGrafico& entorno): personaje(entorno), mapa(entorno) {
    entorno.agregarRendereable(this);

    camara = Camara(&mapa, ventana);
    camara.setObjetivo(personaje);
}

void Escena::render() {
    camara.centrar(renderer);
    mapa.render();
    renderer->setColor(0, 0, 51);
    for (int i = 0; i < mapa.getAncho(); i += 20) {
        renderer->linea(i, 0, i, mapa.getAlto());
    }
    for (int j = 0; j < mapa.getAlto(); j += 20) {
        renderer->linea(0, j, mapa.getAncho(), j);
    }
    personaje.render();
    camara.reiniciar(renderer);

    // DEBUG
    renderer->setColor(51, 0, 51);
    renderer->rectSolido(ventana->getAncho() / 2, ventana->getAlto() / 2, 
                                                                        10, 10);
}

void Escena::manejarEvento(const SDL_Event& event) {
    mapa.manejarEvento(event);
    personaje.manejarEvento(event);
}

void Escena::actualizar() {
    mapa.actualizar();
    personaje.actualizar();
}
