#include "Personaje.h"

// Todo esto se consultaría al servidor.
void Personaje::actualizar() {
    x += velocidadX;
    y += velocidadY;

    // Pared imaginaria, funciona medio feo.
    // if (x <= 0 || x > 1500)
        // x -= velocidadX;
}

void Personaje::moverDerecha() {
    velocidadY = 0;
    velocidadX = 3;
}

void Personaje::moverIzquierda() {
    velocidadY = 0;
    velocidadX = -3;
}

void Personaje::moverArriba() {
    velocidadX = 0;
    velocidadY = -3;
}

void Personaje::moverAbajo() {
    velocidadX = 0;
    velocidadY = 3;
}
void Personaje::detenerse() {
    velocidadX = 0;
    velocidadY = 0;
}
