#include "../controlador/GUI_Chat_Controlador.h"
#include "../modelo/ServidorProxy.h"

GUI_ChatControlador::GUI_ChatControlador(GUI_Chat& vista,
 ServidorProxy& servidor) : GUI_BotonControlador(vista.marco_entrada.x,
  vista.marco_entrada.y, vista.marco_entrada.w, vista.marco_entrada.h),
   chat_vista(vista), servidor(servidor){}

bool GUI_ChatControlador::operator()(SDL_Event& evento) {
	en_foco = enRectangulo(chat_vista.marco_mensajes, evento.button.x, 
															evento.button.y);
	chat_vista.darFoco(en_foco);
	if (!en_foco) {
		SDL_StopTextInput();
		return false;
	}
	return enClick();
}

bool GUI_ChatControlador::enClick(){
	SDL_StartTextInput();
	return true;
}

bool GUI_ChatControlador::ingresarCaracter(SDL_Event& evento){
	if (!en_foco) return false;
	if (evento.type == SDL_TEXTINPUT) {
		chat_vista.entrada += evento.text.text;
		return true;
	} else if (evento.type == SDL_KEYDOWN) {
		switch (evento.key.keysym.scancode) {
			case SDL_SCANCODE_BACKSPACE:
				if(chat_vista.entrada.size() <= 0) break;
				chat_vista.entrada = chat_vista.entrada.substr(0, 
												chat_vista.entrada.size() - 1);
				break;
			case SDL_SCANCODE_RETURN:
				servidor.enviarChat(std::move(chat_vista.entrada));
				chat_vista.entrada.clear();
				break;
			default:
				break;
		}
		return true;
	}
	return false;
}

void GUI_ChatControlador::agregarMensaje(std::string mensaje, 
		bool mensaje_publico) {
	chat_vista.agregarMensaje(mensaje, mensaje_publico);
}

bool GUI_ChatControlador::scroll(SDL_Event& evento){
	if (!en_foco) return false;
	chat_vista.scroll(evento.wheel.y);
	return true;
}

void GUI_ChatControlador::actualizarDimension(){
	rect = chat_vista.marco_entrada;
}
