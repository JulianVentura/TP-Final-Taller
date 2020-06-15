#include "Escena.h"
#include "MovibleVista.h"

Escena::Escena(EntornoGrafico& entorno): personaje(entorno, personajeModelo), 
                            enemigo(entorno, enemigoModelo), mapa(entorno) {
    entorno.agregarRendereable(this);
    camara = Camara(&mapa, ventana);
    camara.setObjetivo(personaje);
}

void Escena::render() {
    camara.centrar(renderer);
    mapa.render();
    
    personaje.render();
    enemigo.render();
    camara.reiniciar(renderer);
}

void Escena::manejarEvento(const SDL_Event& event) {
    mapa.manejarEvento(event);
    personaje.manejarEvento(event);
}

int i = 0;
int maximo = 300;

void Escena::actualizar(unsigned int delta_t) {
    mapa.actualizar(delta_t);
    enemigo.actualizar(delta_t);
    personaje.actualizar(delta_t);
    
    // DEBUG

    int direccion = 4 * i / maximo;
    if (direccion == 0)
        enemigoModelo.moverAbajo();
    else if (direccion == 1)
        enemigoModelo.moverIzquierda();
    else if (direccion == 2)
        enemigoModelo.moverArriba();
    else if (direccion == 3)
        enemigoModelo.moverDerecha();
    i++;
    if (i == maximo) {
        i = 0;
    }
}
