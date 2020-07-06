#include "BuclePrincipal.h"
#include "../vista/GUI_Principal.h"

#include <SDL2/SDL_timer.h>
#include <thread>

#define FPS 60
#define SEG_A_MILLI 1000
#define MILLIS_POR_FRAME SEG_A_MILLI / FPS

BuclePrincipal::BuclePrincipal(Ventana& ventana) : ventana(&ventana) {
    agregarInteractivo(SDL_WINDOWEVENT, &ventana);
    agregarInteractivo(SDL_KEYDOWN, &ventana);
 }

void BuclePrincipal::correr() {
    SDL_Event evento;
    SDL_StopTextInput();
    while (!salir) {
        while (SDL_PollEvent(&evento) != 0) {
			despacharEventos(evento);
        }
        int tiempo = reloj.medir() * SEG_A_MILLI;
        ventana->actualizar(tiempo);
        ventana->render();
        
        int diferencia = MILLIS_POR_FRAME - tiempo;
        if (diferencia > 0) 
            std::this_thread::sleep_for(std::chrono::milliseconds(diferencia));
    }
}

void BuclePrincipal::despacharEventos(SDL_Event& evento) {
    if (evento.type == SDL_QUIT) {
        salir = true;
        return;
	}
    if (interactivos.count(evento.type) <= 0) return;
    bool evento_consumido = false;
    for (auto& interactivo : interactivos[evento.type]) {
        if (!interactivo) continue;
        evento_consumido = interactivo->manejarEvento(evento);
        if (evento_consumido) break;
    }
}

void BuclePrincipal::agregarInteractivo(Uint32 tipo_evento, IInteractivo* interactivo) {
    interactivos[tipo_evento].push_back(interactivo);
}
