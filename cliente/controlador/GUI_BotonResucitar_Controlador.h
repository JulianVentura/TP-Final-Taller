#ifndef __BOTON_RESUCITAR_CONTROLADOR_H__
#define __BOTON_RESUCITAR_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonResucitar.h"

/*
*	Ver GUI_Boton_Controlador.
*/

class GUI_BotonResucitarControlador final : public GUI_BotonControlador{
private:
	ServidorProxy& servidor;
	// Envía al servidor la operación de resurrección.
	bool enClick() override;
public:
	GUI_BotonResucitarControlador(GUI_BotonResucitar& vista,
	 ServidorProxy& servidor);
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/