#include "Ventana.h"
#include "ErrorGrafico.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

void Ventana::agregarRendereable(IRendereable* rendereable) {
    rendereables.push_back(rendereable);
    rendereable->setRenderer(renderer);
    rendereable->setVentana(this);
}

void Ventana::agregarInteractivo(IInteractivo* interactivo) {
    interactivos.push_back(interactivo);
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
        if (event.key.keysym.sym == SDLK_F11) {
            pantalla_completa = !pantalla_completa;
            int flags = (pantalla_completa) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
            SDL_SetWindowFullscreen(ventana, flags);
        }
    }
    
    if (event.type == SDL_WINDOWEVENT) { 
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            SDL_GetWindowSize(ventana, &ancho, &alto);
        }
    }

    for (auto& interactivo: interactivos) {
        interactivo->manejarEvento(event);
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
