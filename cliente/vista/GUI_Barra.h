#ifndef __GUI_BARRA_H__
#define __GUI_BARRA_H__

#include <SDL2/SDL_render.h>
#include <atomic>

#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/Colores.h"

class GUI_Barra : public IRendereable{
private:
	Colores& paleta;
	SDL_Color& principal,secundario;
protected:
	SDL_Rect marco;
	std::atomic<int> &capacidad_max, &capacidad_actual;
public:
	GUI_Barra(EntornoGrafico& entorno, Colores& paleta, SDL_Color& principal,
	 SDL_Color& secundario, std::atomic<int>& capacidad_max,
	  std::atomic<int>& capacidad_actual);
	void render();
	virtual ~GUI_Barra() = 0;
};

#endif /*__GUI_BARRA_H__*/