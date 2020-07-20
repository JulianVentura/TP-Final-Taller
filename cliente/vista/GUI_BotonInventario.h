#ifndef __GUI_BOTON_INVENTARIO_H__
#define __GUI_BOTON_INVENTARIO_H__

#include "../vista/GUI_Boton.h"

class GUI_BotonInventario final : public GUI_Boton{
public:
	GUI_BotonInventario(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/
