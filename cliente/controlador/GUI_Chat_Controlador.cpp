#include "../controlador/GUI_Chat_Controlador.h"
#include "../modelo/ServidorProxy.h"

GUI_ChatControlador::GUI_ChatControlador(GUI_Chat& vista,
 ServidorProxy& servidor) : GUI_CajaTextoControlador(vista),
   chat_vista(vista), servidor(servidor){}

bool GUI_ChatControlador::enEnter(){
	servidor.enviarChat(std::move(chat_vista.entrada));
	chat_vista.entrada.clear();
	return true;
}

void GUI_ChatControlador::agregarMensaje(std::string mensaje,
 bool mensaje_publico){
	chat_vista.agregarMensaje(mensaje, mensaje_publico);
}

void GUI_ChatControlador::scroll(SDL_Event& evento){
	chat_vista.scroll(evento.wheel.y);
}

void GUI_ChatControlador::actualizarDimension(){
	rect = chat_vista.marco_entrada;
}
