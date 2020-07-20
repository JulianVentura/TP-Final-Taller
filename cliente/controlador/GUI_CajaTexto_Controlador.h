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
	bool enClick() override;
	virtual bool enEnter();
public:
	GUI_CajaTextoControlador(GUI_CajaTexto& vista);
	bool manejarEvento(SDL_Event& evento) override;
	bool operator()(SDL_Event& evento) override;
	void darFoco(bool enFoco);
	void actualizarDimension();
};

#endif /*__CAJA_TEXTO_H__*/