#ifndef __GUI_CLICKEABLE_H__
#define __GUI_CLICKEABLE_H__

#include <SDL2/SDL.h>
#include "../vista/GUI_Boton.h"

/*
*	Clase base de todo elemento interactuable de la interfaz.
*/

class GUI_Clickeable{
protected:
	SDL_Rect rect = {};
	virtual bool enClick() = 0;
public:
	GUI_Clickeable(SDL_Rect rect);

	/* Espera recibir un evento de la familia SDL_MouseButtonEvent.
	*  Verifica si la posición absoluta del ratón está contenida en "rect",
	*  de ser así llama a enClick.
	*/
	virtual bool operator()(SDL_Event& evento);
};

#endif /*__GUI_CLICKEABLE_CONTROLADOR_H__*/