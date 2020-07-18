#ifndef __GUI_ORO_ALMACENADO_H__
#define __GUI_ORO_ALMACENADO_H__

#include "../vista/GUI_Panel.h"
#include "../vista/GUI_BotonOro.h"

class GUI_OroAlmacenado : public GUI_BotonOro{
private:
	std::atomic<uint32_t>& oro;
public:
	GUI_OroAlmacenado(EntornoGrafico& entorno, Colores& paleta,
	 std::atomic<uint32_t>& oro);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_ORO_ALMACENADO_H__*/