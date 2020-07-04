#include "BuclePrincipal.h"
#include "../vista/GUI_Principal.h"

#include <SDL2/SDL_timer.h>
#include <thread>

#define FPS 60
#define SEG_A_MILLI 1000
#define MILLIS_POR_FRAME SEG_A_MILLI / FPS

BuclePrincipal::BuclePrincipal(Ventana& ventana, GUI_Principal& gui, 
        ServidorProxy& servidor) : ventana(&ventana), gui(gui), 
        servidor(servidor) {
     agregarInteractivo(&ventana);
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
        for (auto& rendereable: rendereables) {
            rendereable->actualizar(tiempo);
        }
        for (auto& rendereable: rendereables) {
            rendereable->render();
        }
        ventana->render();
        
        int diferencia = MILLIS_POR_FRAME - tiempo;
        if (diferencia > 0) 
            std::this_thread::sleep_for(std::chrono::milliseconds(diferencia));
    }
}


void BuclePrincipal::despacharEventos(SDL_Event& evento) {
    bool evento_consumido = false;

	switch(evento.type) {
		case SDL_QUIT: 
			salir = true;
		break;

		case SDL_MOUSEBUTTONDOWN:
            for(auto& boton : gui.botones){
                evento_consumido = (*boton)(evento);
                if(evento_consumido) break;
            }
            //if(!evento_consumido) escena.manejarEvento(evento);
			break;

        case SDL_MOUSEWHEEL:
            gui.chat_controlador.scroll(evento);
        break;

        case SDL_KEYDOWN:
        case SDL_TEXTINPUT:
            if(gui.chat_controlador.ingresarCaracter(evento)){
                ventana->manejarEvento(evento);
                for (auto& interactivo : interactivos){
                    interactivo -> manejarEvento(evento);
                }
            }
        break;
        
        case SDL_WINDOWEVENT:
            ventana->manejarEvento(evento);
            gui.actualizarDimension();
        break;
	}
}

void BuclePrincipal::agregarInteractivo(IInteractivo* interactivo) {
    interactivos.push_back(interactivo);
}

void BuclePrincipal::agregarRendereable(IRendereable* rendereable) {
    rendereables.push_back(rendereable);
}
