#ifndef __GUI_CHAT_CONTROLADOR_H__
#define __GUI_CHAT_CONTROLADOR_H__

#include <SDL2/SDL.h>
#include <string>

#include "../modelo/ServidorProxy.h"
#include "../vista/GUI_Chat.h"
#include "../controlador/GUI_Boton_Controlador.h"

class GUI_ChatControlador;
class ServidorProxy;

class GUI_ChatControlador : public GUI_BotonControlador{
private:
	GUI_Chat& chat_vista;

public:
	explicit GUI_ChatControlador(GUI_Chat& vista);
	bool ingresarCaracter(SDL_Event& evento, ServidorProxy& servidor);
	void agregarMensaje(std::string& mensaje);
	void scroll(SDL_Event& evento);
	bool operator()(SDL_Event& evento) override;
	bool enClick();
	void actualizarDimension();
};

#endif /*__GUI_CHAT_CONTROLADOR_H__*/