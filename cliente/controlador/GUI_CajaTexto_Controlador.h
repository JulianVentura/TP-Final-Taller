#ifndef __GUI_CAJA_TEXTO_CONTROLADOR_H__
#define __GUI_CAJA_TEXTO_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../vista/GUI_CajaTexto.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "IInteractivo.h"

class GUI_CajaTextoControlador : public GUI_Clickeable, public IInteractivo {
protected:
	GUI_CajaTexto& caja_vista;
	bool enFoco = false;
	// Gana foco y habilita el ingreso de texto de SDL.
	bool enClick() override;
	virtual bool enEnter();
public:
	GUI_CajaTextoControlador(GUI_CajaTexto& vista);

	// Espera eventos de las familias SDL_KeyboardEvent o SDL_TextInputEvent.
	// Modifica el campo de texto de vista, si se encuentra en foco.
	bool manejarEvento(SDL_Event& evento) override;

	// Se sobreescribe el método para perder el foco cuando el click se 
	// realiza fuera del área.
	bool operator()(SDL_Event& evento) override;

	void darFoco(bool enFoco);
	void actualizarDimension();
};

#endif /*__CAJA_TEXTO_H__*/