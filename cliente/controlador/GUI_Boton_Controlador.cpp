#include <SDL2/SDL.h>

#include "GUI_Boton_Controlador.h"

bool enRectangulo(SDL_Rect& rect, int x, int y){
	return (x > rect.x && y > rect.y && x < rect.x + rect.w
	 && y < rect.y + rect.h);
}

GUI_BotonControlador::GUI_BotonControlador(int x, int y, int ancho, int alto){
	rect.x = x;
	rect.y = y;
	rect.w = ancho;
	rect.h = alto;
}

bool GUI_BotonControlador::operator()(SDL_Event& evento){
	if(!enRectangulo(rect, evento.button.x, evento.button.y)) return false;
	return enClick();
}

GUI_BotonControlador::~GUI_BotonControlador(){
}
