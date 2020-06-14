#ifndef __GUI_BOTON_INVENTARIO_H__
#define __GUI_BOTON_INVENTARIO_H__

#include "IRendereable.h"
#include "Imagen.h"

class GUI_BotonInventario final : public IRendereable{
public:
	Imagen imagen;
	bool visible;
	GUI_BotonInventario(EntornoGrafico& entorno, int x, int y);
	void render();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/