#ifndef __GUI_BOTON_ORO_H__
#define __GUI_BOTON_ORO_H__

#include <SDL2/SDL_render.h>
#include <atomic>

#include "../vista/Imagen.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"

class GUI_BotonOro  : public IRendereable{
private:
	Colores& paleta;
	std::atomic<uint16_t>& oro;
public:
	SDL_Rect marco;
	Imagen imagen;
	GUI_BotonOro(EntornoGrafico& entorno, Colores& paleta,
	 std::atomic<uint16_t>& oro);
	void render();
	void actualizarDimension();
};

#endif /*__GUI_BOTON_ORO_H__*/
