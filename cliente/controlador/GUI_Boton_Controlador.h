#ifndef __GUI_BOTON_CONTROLADOR_H__
#define __GUI_BOTON_CONTROLADOR_H__

#include <SDL2/SDL.h>
#include "../vista/GUI_Boton.h"
#include "GUI_Clickeable.h"

class GUI_BotonControlador : public GUI_Clickeable{
protected:
	GUI_Boton& vista;
	virtual bool enClick() = 0;
public:
	GUI_BotonControlador(GUI_Boton& vista);
	virtual bool operator()(SDL_Event& evento);
	virtual void actualizarDimension();
};

#endif /*__GUI_BOTON_CONTROLADOR_H__*/
