#include "GUI_CajaTexto_Controlador.h"

GUI_CajaTextoControlador::GUI_CajaTextoControlador(GUI_CajaTexto& vista): 
 GUI_Clickeable(vista.marco_entrada), caja_vista(vista) {
	actualizarDimension();
 }

void GUI_CajaTextoControlador::darFoco(bool enFoco) {
	this->enFoco = enFoco;
	caja_vista.darFoco(enFoco);
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
	SDL_Point punto = {evento.button.x, evento.button.y};
	enFoco = SDL_PointInRect(&punto, &rect);
	caja_vista.darFoco(enFoco);
	return enFoco && enClick();
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