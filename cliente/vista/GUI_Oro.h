#ifndef __GUI_ORO_H__
#define __GUI_ORO_H__

#include <SDL2/SDL_render.h>
#include <atomic>

#include "../vista/Imagen.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"

class GUI_Oro  : public IRendereable{
private:
	Imagen imagen;
	SDL_Rect marco;
	Colores& paleta;
	std::atomic<uint16_t>& oro;
public:
	GUI_Oro(EntornoGrafico& entorno, Colores& paleta, std::atomic<uint16_t>& oro);
	void render();
	void actualizarDimension();
};

#endif /*__GUI_ORO_H__*/
