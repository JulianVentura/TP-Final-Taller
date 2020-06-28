#include "Ventana.h"
#include "ErrorGrafico.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

void Ventana::agregarRendereable(IRendereable* rendereable) {
    rendereables.push_back(rendereable);
    rendereable->setRenderer(renderer);
    rendereable->setVentana(this);
}

int Ventana::getAlto() {
    return alto;
}

int Ventana::getAncho() {
    return ancho;
}

Ventana::~Ventana() {
    SDL_DestroyWindow(ventana);
}

Ventana::Ventana(EntornoGrafico& entorno, const char* title): entorno(entorno) {
    ventana = SDL_CreateWindow(title, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        ancho, alto, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
    
    if (event.type == SDL_WINDOWEVENT) { 
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            SDL_GetWindowSize(ventana, &ancho, &alto);
        }
    }
}

void Ventana::actualizar(unsigned int delta_t) {
    for (auto& rendereable: rendereables) 
        rendereable->actualizar(delta_t);
}

void Ventana::render() {
    renderer->setColor(color_fondo);
    renderer->limpiar();
    for (auto& rendereable: rendereables) 
        rendereable->render();
    renderer->presentar();
}
