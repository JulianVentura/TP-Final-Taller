#include "../controlador/GUI_Chat_Controlador.h"
#include "../modelo/ServidorProxy.h"

GUI_ChatControlador::GUI_ChatControlador(GUI_Chat& vista,
 ServidorProxy& servidor) : GUI_CajaTextoControlador(vista),
   chat_vista(vista), servidor(servidor) {}

bool GUI_ChatControlador::enEnter(){
	servidor.enviarChat(std::move(chat_vista.entrada));
	chat_vista.entrada.clear();
	return true;
}

bool GUI_ChatControlador::operator()(SDL_Event& evento) {
	SDL_Point punto = {evento.button.x, evento.button.y};
	enFoco = SDL_PointInRect(&punto, &rect);
	chat_vista.darFoco(enFoco);
	if (!enFoco) {
		SDL_StopTextInput();
		return false;
	}
	return enClick();
}

bool GUI_ChatControlador::enClick(){
	SDL_StartTextInput();
	return true;
}

void GUI_ChatControlador::agregarMensaje(std::string mensaje, 
		bool mensaje_publico) {
	chat_vista.agregarMensaje(mensaje, mensaje_publico);
}

bool GUI_ChatControlador::scroll(SDL_Event& evento){
	if (!enFoco) return false;
	chat_vista.scroll(evento.wheel.y);
	return true;
}

void GUI_ChatControlador::actualizarDimension(){
	rect = chat_vista.marco_entrada;
}
