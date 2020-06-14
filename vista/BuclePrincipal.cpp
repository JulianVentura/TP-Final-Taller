#include "BuclePrincipal.h"

void BuclePrincipal::correr() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) quit = true;
            ventana->manejarEvento(event);
        }
        ventana->render();
    }
}
