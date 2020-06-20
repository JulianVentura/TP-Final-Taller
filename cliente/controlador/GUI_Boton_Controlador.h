#ifndef __GUI_BOTON_CONTROLADOR_H__
#define __GUI_BOTON_CONTROLADOR_H__

#include <SDL2/SDL.h>

bool enRectangulo(SDL_Rect& rect, int x, int y);

class GUI_BotonControlador{
protected:
	SDL_Rect rect;
	virtual bool enClick() = 0;
public:
	GUI_BotonControlador(int x, int y, int ancho, int alto);
	virtual bool operator()(SDL_Event& evento);
	virtual ~GUI_BotonControlador();
};

#endif /*__GUI_BOTON_CONTROLADOR_H__*/
