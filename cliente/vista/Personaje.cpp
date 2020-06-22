#include "Personaje.h"

// Todo esto se consultaría al servidor.
void Personaje::actualizar() {
    x += velocidadX;
    y += velocidadY;
}

void Personaje::moverDerecha() {
    velocidadY = 0;
    velocidadX = 2;
}

void Personaje::moverIzquierda() {
    velocidadY = 0;
    velocidadX = -2;
}

void Personaje::moverArriba() {
    velocidadX = 0;
    velocidadY = -2;
}

void Personaje::moverAbajo() {
    velocidadX = 0;
    velocidadY = 2;
}
void Personaje::detenerse() {
    velocidadX = 0;
    velocidadY = 0;
}
