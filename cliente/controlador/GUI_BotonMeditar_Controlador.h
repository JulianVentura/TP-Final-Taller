#ifndef __BOTON_MEDITAR_CONTROLADOR_H__
#define __BOTON_MEDITAR_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonMeditar.h"

class GUI_BotonMeditarControlador final : public GUI_BotonControlador{
private:
	ServidorProxy& servidor;
	bool enClick() override;
public:
	GUI_BotonMeditarControlador(GUI_BotonMeditar& vista,
	 ServidorProxy& servidor);
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/