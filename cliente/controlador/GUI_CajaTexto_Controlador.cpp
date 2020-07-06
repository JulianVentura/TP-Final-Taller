#include "GUI_CajaTexto_Controlador.h"

GUI_CajaTextoControlador::GUI_CajaTextoControlador(GUI_CajaTexto& vista)
: GUI_BotonControlador(vista.marco_entrada.x, vista.marco_entrada.y,
 vista.marco_entrada.w, vista.marco_entrada.h),
caja_vista(vista){
	enFoco = false;
}

bool GUI_CajaTextoControlador::manejarEvento(SDL_Event& evento) {
	if(!enFoco) return false;
	if(evento.type == SDL_TEXTINPUT){
		caja_vista.entrada += evento.text.text;
		return true;
	} else if (evento.type == SDL_KEYDOWN) {
		switch(evento.key.keysym.scancode){
			case SDL_SCANCODE_BACKSPACE:
				if(caja_vista.entrada.size() <= 0) break;
				caja_vista.entrada = caja_vista.entrada.substr(0, 
					caja_vista.entrada.size() - 1);
				break;
			case SDL_SCANCODE_RETURN:
				enEnter();
			default:
			break;
		}
		return true;
	}
	return false;
}

bool GUI_CajaTextoControlador::operator()(SDL_Event& evento){
	if(!enRectangulo(rect, evento.button.x, evento.button.y)){
		enFoco = false;
		return false;
	}
	return enClick();
}

bool GUI_CajaTextoControlador::enEnter(){
	return true;
}

bool GUI_CajaTextoControlador::enClick(){
	enFoco = true;
	return true;
}

void GUI_CajaTextoControlador::actualizarDimension(){
	rect = caja_vista.marco_entrada;
}