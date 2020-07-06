#include "BucleLogin.h"

BucleLogin::BucleLogin(Ventana& ventana, GUI_Login& gui, 
        ServidorProxy& servidor) : ventana(&ventana), gui(gui), 
        servidor(servidor) {
}

void BucleLogin::correr() {
    SDL_Event evento;
    SDL_StartTextInput();
    while (!salir) {
        while (SDL_PollEvent(&evento)) {
			despacharEventos(evento);
        }

        int tiempo = reloj.medir() * SEG_A_MILLI;
        ventana->actualizar(tiempo);
        ventana->render();
        
        int diferencia = MILLIS_POR_FRAME - tiempo;
        if (diferencia > 0) 
            std::this_thread::sleep_for(std::chrono::milliseconds(diferencia));
    }
    SDL_StopTextInput();
}


void BucleLogin::despacharEventos(SDL_Event& evento) {
    bool evento_consumido = false;
	switch(evento.type) {
		case SDL_QUIT: 
			salir = true;
		break;

		case SDL_MOUSEBUTTONDOWN:
            for(auto& boton : gui.botones){
                evento_consumido = (*boton)(evento) || evento_consumido;
            }
            if(evento_consumido){
                SDL_StartTextInput();
            } else{
                SDL_StopTextInput();
            }
			break;

        case SDL_KEYDOWN:
        case SDL_TEXTINPUT:
            gui.manejarEvento(evento);
        break;
        
        case SDL_WINDOWEVENT:
            ventana->manejarEvento(evento);
            gui.actualizarDimension();
        break;

        default:
        break;
	}
}

void BucleLogin::agregarInteractivo(IInteractivo* interactivo) {
    interactivos.push_back(interactivo);
}

