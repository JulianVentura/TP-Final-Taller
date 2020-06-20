#include "BuclePrincipal.h"

#include <SDL2/SDL_timer.h>

BuclePrincipal::BuclePrincipal(Ventana& ventana) : ventana(&ventana) {
    ultima_actualizacion = SDL_GetTicks();
}

void BuclePrincipal::correr() {
    SDL_Event event;
     SDL_StopTextInput();
    while (!salir) {
        while (SDL_PollEvent(&event) != 0) {
			despacharEventos(event);
            ventana->manejarEvento(event);
        }
        unsigned int actualizacion_temp = SDL_GetTicks();
        ventana->actualizar(actualizacion_temp - ultima_actualizacion);
        ventana->render();
        ultima_actualizacion = actualizacion_temp;
    }
}

void BuclePrincipal::despacharEventos(SDL_Event& event) {
	switch(event.type) {
		case SDL_QUIT: 
			salir = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			for(auto& boton : botones)
				if((*boton)(event)) break;
			break;

        case SDL_MOUSEWHEEL:
            chat -> scroll(event);
            break;

        case SDL_KEYDOWN:
        case SDL_TEXTINPUT:
            chat -> ingresarCaracter(event);
            break;
	}
}
