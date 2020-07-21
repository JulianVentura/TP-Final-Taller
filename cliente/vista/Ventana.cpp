#include "Ventana.h"
#include "ErrorGrafico.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#define ANCHO_VENTANA_INIT 650
#define ALTO_VENTANA_INIT 500

Ventana::~Ventana() {
    SDL_DestroyWindow(ventana);
}

Ventana::Ventana(EntornoGrafico& entorno, const char* title): 
                                                            entorno(entorno) {
    this->ancho = ANCHO_VENTANA_INIT;
    this->alto = ALTO_VENTANA_INIT;
    ventana = SDL_CreateWindow(title, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        ancho, alto, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!ventana)
        throw ErrorGrafico("No se pudo crear la ventana %s\n", SDL_GetError());
    entorno.setVentana(this);
}

void Ventana::agregarRendereable(IRendereable* rendereable) {
    rendereables.push_back(rendereable);
}

void Ventana::borrarRendereables() {
    rendereables.clear();    
}

bool Ventana::manejarEvento(SDL_Event& evento) {
    if (evento.type == SDL_KEYDOWN) {
        if (evento.key.keysym.sym == SDLK_F11) {
            pantalla_completa = !pantalla_completa;
            int flags = (pantalla_completa) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
            SDL_SetWindowFullscreen(ventana, flags);
            return true;
        }
    }
    if (evento.type == SDL_WINDOWEVENT) { 
        if (evento.window.event == SDL_WINDOWEVENT_RESIZED) {
            SDL_GetWindowSize(ventana, &ancho, &alto);
        }
    }
    return false;
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
