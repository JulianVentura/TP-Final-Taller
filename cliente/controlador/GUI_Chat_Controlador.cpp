#include "../controlador/GUI_Chat_Controlador.h"

GUI_ChatControlador::GUI_ChatControlador(GUI_Chat& vista)
 : GUI_BotonControlador(vista.marco_entrada.x, vista.marco_entrada.y,
  vista.marco_entrada.w, vista.marco_entrada.h), chat_vista(vista){}

bool GUI_ChatControlador::operator()(SDL_Event& evento){
	if(!enRectangulo(rect, evento.button.x, evento.button.y)){
		SDL_StopTextInput();
		return false;
	}
	return enClick();
}

bool GUI_ChatControlador::enClick(){
	SDL_StartTextInput();
	return true;
}

void GUI_ChatControlador::ingresarCaracter(SDL_Event& evento){
	if(evento.type == SDL_TEXTINPUT){
		chat_vista.entrada += evento.text.text;
		return;
	}
	
	switch(evento.key.keysym.scancode){
			case SDL_SCANCODE_BACKSPACE:
			if(chat_vista.entrada.size() > 0)
				chat_vista.entrada = chat_vista.entrada.substr(0, 
					chat_vista.entrada.size() - 1);
			break;

			case SDL_SCANCODE_RETURN:
			chat_vista.agregarMensaje(std::move(chat_vista.entrada));
			chat_vista.entrada.clear();
			break;

			default:
			break;
	}
}

void GUI_ChatControlador::scroll(SDL_Event& evento){
	chat_vista.scroll(evento.wheel.y);
}

void GUI_ChatControlador::actualizarDimension(){
	rect = chat_vista.marco_entrada;
}