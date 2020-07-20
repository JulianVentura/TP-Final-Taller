#ifndef __GUI_BOTON_ORO_H__
#define __GUI_BOTON_ORO_H__

#include <atomic>

#include "../vista/GUI_Boton.h"

class GUI_BotonOro  : public GUI_Boton{
private:
	Colores& paleta;
	std::atomic<uint16_t>& oro;
	SDL_Rect marco;
public:
	GUI_BotonOro(EntornoGrafico& entorno, Colores& paleta,
	 std::atomic<uint16_t>& oro);
	void render();
	void actualizarDimension();
};

#endif /*__GUI_BOTON_ORO_H__*/
