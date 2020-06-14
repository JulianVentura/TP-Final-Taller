#include "BuclePrincipal.h"
#include <SDL2/SDL_timer.h>

BuclePrincipal::BuclePrincipal(Ventana& ventana) : ventana(&ventana) {
    ultima_actualizacion = SDL_GetTicks();
}


void BuclePrincipal::correr() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) quit = true;
            ventana->manejarEvento(event);
        }
        unsigned int actualizacion_temp = SDL_GetTicks();
        ventana->actualizar(actualizacion_temp - ultima_actualizacion);
        ventana->render();
        ultima_actualizacion = actualizacion_temp;
    }
}
