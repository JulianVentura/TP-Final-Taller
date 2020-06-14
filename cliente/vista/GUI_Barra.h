#ifndef __GUI_BARRA_H__
#define __GUI_BARRA_H__

#include <SDL2/SDL_render.h>

#include "EntornoGrafico.h"
#include "IRendereable.h"

class Barra final: public IRendereable{
private:
	SDL_Rect marco;
	SDL_Color principal,secundario;
public:
	int capacidad_max, capacidad_actual;
	Barra(EntornoGrafico& entorno, SDL_Rect& marco, SDL_Color& color,
	int capacidad_max, int capacidad_actual);
	void render();
};

#endif /*__GUI_BARRA_H__*/