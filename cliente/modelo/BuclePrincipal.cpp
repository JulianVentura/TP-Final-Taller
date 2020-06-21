#include "BuclePrincipal.h"
#include "../vista/GUI_Principal.h"

#include <SDL2/SDL_timer.h>
#include <thread>
#define FPS 60
#define SEG_A_MILLI 1000
#define MILLIS_POR_FRAME SEG_A_MILLI / FPS

BuclePrincipal::BuclePrincipal(Ventana& ventana, GUI_Principal& gui)
 : ventana(&ventana), gui(gui) {}

void BuclePrincipal::correr() {
    SDL_Event event;
    SDL_StopTextInput();
    while (!salir) {
        while (SDL_PollEvent(&event) != 0) {
            ventana->manejarEvento(event);
			despacharEventos(event);
        }
        int tiempo = reloj.medir() * SEG_A_MILLI;
        ventana->actualizar(tiempo);
        ventana->render();
        int diferencia = MILLIS_POR_FRAME - tiempo;
        if (diferencia > 0) 
            std::this_thread::sleep_for(std::chrono::milliseconds(diferencia));
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
            gui.chat_controlador.ingresarCaracter(event);
            break;
        
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                 gui.actualizarDimension();
            break;
	}
}
