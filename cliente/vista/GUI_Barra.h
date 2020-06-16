#ifndef __GUI_BARRA_H__
#define __GUI_BARRA_H__

#include <SDL2/SDL_render.h>

#include "EntornoGrafico.h"
#include "IRendereable.h"

class GUI_Barra : public IRendereable{
private:
	SDL_Color principal,secundario;
protected:
	SDL_Rect marco;
	int& capacidad_max;
	int& capacidad_actual;
public:
	GUI_Barra(EntornoGrafico& entorno, SDL_Color& color,int& capacidad_max,
		int& capacidad_actual);
	void render();
	virtual ~GUI_Barra() = 0;
};

#endif /*__GUI_BARRA_H__*/