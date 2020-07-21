#ifndef __GUI_CLICKEABLE_H__
#define __GUI_CLICKEABLE_H__

#include <SDL2/SDL.h>
#include "../vista/GUI_Boton.h"

class GUI_Clickeable{
protected:
	SDL_Rect rect = {};
	virtual bool enClick() = 0;
public:
	GUI_Clickeable(SDL_Rect rect);
	virtual bool operator()(SDL_Event& evento);
};

#endif /*__GUI_CLICKEABLE_CONTROLADOR_H__*/