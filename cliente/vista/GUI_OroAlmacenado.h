#ifndef __GUI_ORO_ALMACENADO_H__
#define __GUI_ORO_ALMACENADO_H__

#include <SDL2/SDL_render.h>
#include <atomic>

#include "../vista/Imagen.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/GUI_Panel.h"

class GUI_OroAlmacenado : public IRendereable{
private:
	Colores& paleta;
	std::atomic<uint16_t>& oro;
	SDL_Rect marco;
	Imagen imagen;
public:
	GUI_OroAlmacenado(EntornoGrafico& entorno, Colores& paleta,
	 std::atomic<uint16_t>& oro);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_ORO_ALMACENADO_H__*/