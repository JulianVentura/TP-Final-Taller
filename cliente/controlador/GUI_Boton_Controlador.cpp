#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "GUI_Boton_Controlador.h"

GUI_BotonControlador::GUI_BotonControlador(GUI_Boton& uvista) :
GUI_Clickeable(uvista.obtenerMarco()), vista(uvista) {
	rect = {};
	actualizarDimension();
}

void GUI_BotonControlador::actualizarDimension(){
	rect = vista.obtenerMarco();
}

bool GUI_BotonControlador::operator()(SDL_Event& evento){
	if (evento.type != SDL_MOUSEBUTTONDOWN) return false;
	SDL_Point punto = {evento.button.x, evento.button.y};
	if(!SDL_PointInRect(&punto, &rect)) return false;
	return enClick();
}
