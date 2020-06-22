#include "BuclePrincipal.h"
#include "../vista/GUI_Principal.h"

#include <SDL2/SDL_timer.h>

BuclePrincipal::BuclePrincipal(Ventana& ventana, GUI_Principal& gui,
    ServidorProxy& servidor)
 : ventana(&ventana), gui(gui), servidor(servidor) {
    ultima_actualizacion = SDL_GetTicks();
}

void BuclePrincipal::correr() {
    SDL_Event event;
     SDL_StopTextInput();
    while (!salir) {
        while (SDL_PollEvent(&event) != 0) {
            ventana->manejarEvento(event);
			despacharEventos(event);
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
			for(auto& boton : gui.botones)
				if((*boton)(event)) break;
			break;

        case SDL_MOUSEWHEEL:
            gui.chat_controlador.scroll(event);
            break;

        case SDL_KEYDOWN:
        case SDL_TEXTINPUT:
            gui.chat_controlador.ingresarCaracter(event, servidor);
            break;
        
        case SDL_WINDOWEVENT:
            gui.actualizarDimension();
            break;
	}
}
