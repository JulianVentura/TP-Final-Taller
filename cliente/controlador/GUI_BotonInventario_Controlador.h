#ifndef __GUI_BOTON_INVENTARIO_CONTROLADOR_H__
#define __GUI_BOTON_INVENTARIO_CONTROLADOR_H__

#include "GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonInventario.h"

class GUI_BotonInventarioControlador : public GUI_BotonControlador{
private:
	GUI_BotonInventario& vista;
	bool enClick();
public:
	GUI_BotonInventarioControlador(GUI_BotonInventario& vista, int x, int y, int ancho, int largo);
};

#endif /*__GUI_BOTON_INVENTARIO_CONTROLADOR_H__*/
