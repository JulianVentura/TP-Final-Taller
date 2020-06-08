#include "Ventana.h"
#include "ErrorGrafico.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

void Ventana::addRenderable(IRenderable* renderable) {
    renderables.push_back(renderable);
    renderable->setRenderer(renderer);
    renderable->setVentana(this);
}

void Ventana::addInteractivo(IInteractivo* interactivo) {
    interactivos.push_back(interactivo);  
}

int Ventana::getAlto() {
    SDL_GetWindowSize(ventana, &width, &height);
    return height;
}

int Ventana::getAncho() {
    SDL_GetWindowSize(ventana, &width, &height);
    return width;
}

Ventana::~Ventana() {
    SDL_DestroyWindow(ventana);
}

Ventana::Ventana(EntornoGrafico& entorno, const char* title): entorno(entorno) {
    ventana = SDL_CreateWindow(title, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!ventana)
        throw ErrorGrafico("No se pudo crear la ventana %s\n", SDL_GetError());
    entorno.setVentana(this);
}

void Ventana::manejarEvento(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            SDL_SetWindowFullscreen(ventana, 0);
        }
        if (event.key.keysym.sym == SDLK_F11) {
            SDL_SetWindowFullscreen(ventana, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
    }
    if (event.type == SDL_MOUSEBUTTONUP) {   
    }

    for (auto& interactivo: interactivos) {
        interactivo->manejarEvento(event);
    }
}

void Ventana::render() {
    renderer->setColor(color_fondo);
    renderer->clear();
    for (auto& renderable: renderables) {
        renderable->render();
    }
    renderer->present();
}
