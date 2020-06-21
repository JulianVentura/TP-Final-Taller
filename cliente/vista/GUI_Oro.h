#ifndef __GUI_ORO_H__
#define __GUI_ORO_H__

#include <SDL2/SDL_render.h>

#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"

class GUI_Oro  : public IRendereable{
private:
	SDL_Rect marco;
	Colores& paleta;
	
public:
	int oro;
	explicit GUI_Oro(EntornoGrafico& entorno, Colores& paleta);
	void render();
	void actualizarDimension();
};

#endif /*__GUI_ORO_H__*/