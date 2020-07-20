#ifndef __BOTON_RESUCITAR_CONTROLADOR_H__
#define __BOTON_RESUCITAR_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonResucitar.h"

class GUI_BotonResucitarControlador : public GUI_BotonControlador{
private:
	GUI_BotonResucitar& vista;
	ServidorProxy& servidor; 
public:
	GUI_BotonResucitarControlador(GUI_BotonResucitar& vista,
	 ServidorProxy& servidor);
	bool enClick() override;
	void actualizarDimension();
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/