#include "Escena.h"

Escena::Escena(EntornoGrafico& entorno): personaje(entorno, personajeModelo), 
                                                                mapa(entorno) {
    entorno.agregarRendereable(this);

    camara = Camara(&mapa, ventana);
    camara.setObjetivo(personaje);
}

void Escena::render() {
    camara.centrar(renderer);
    mapa.render();
    
    personaje.render();
    camara.reiniciar(renderer);
}

void Escena::manejarEvento(const SDL_Event& event) {
    mapa.manejarEvento(event);
    personaje.manejarEvento(event);
}

void Escena::actualizar(unsigned int delta_t) {
    mapa.actualizar(delta_t);
    personaje.actualizar(delta_t);
}
