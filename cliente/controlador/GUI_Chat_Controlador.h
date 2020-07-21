#ifndef __GUI_CHAT_CONTROLADOR_H__
#define __GUI_CHAT_CONTROLADOR_H__

#include <SDL2/SDL.h>
#include <string>

#include "../modelo/ServidorSalida.h"
#include "../vista/GUI_Chat.h"
#include "../controlador/GUI_CajaTexto_Controlador.h"

class ServidorProxy;

class GUI_ChatControlador : public GUI_CajaTextoControlador,
 public ServidorSalida{
private:
	GUI_Chat& chat_vista;
	ServidorProxy& servidor;
	bool enEnter() override;

public:
	GUI_ChatControlador(GUI_Chat& vista, ServidorProxy& servidor);
	void agregarMensaje(std::string mensaje, bool mensaje_publico) override;

	// Espera eventos de la familia SDL_MouseWheelEvent.
	bool scroll(SDL_Event& evento);
	
	bool operator()(SDL_Event& evento) override;
	bool enClick() override;
	void actualizarDimension();
};

#endif /*__GUI_CHAT_CONTROLADOR_H__*/
