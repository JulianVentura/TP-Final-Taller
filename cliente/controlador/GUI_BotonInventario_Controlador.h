#ifndef __GUI_BOTON_INVENTARIO_CONTROLADOR_H__
#define __GUI_BOTON_INVENTARIO_CONTROLADOR_H__

#include "GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonInventario.h"
#include "../vista/GUI_PanelInventario.h"

#define ALTO_INVENTARIO  5
#define ANCHO_INVENTARIO 3

class GUI_BotonInventarioControlador : public GUI_BotonControlador{
private:
	char inventario[ANCHO_INVENTARIO][ALTO_INVENTARIO];
	GUI_BotonInventario& vista_boton;
	GUI_PanelInventario& vista_inventario;
	bool enClick();
public:
	void actualizarDimension();
	GUI_BotonInventarioControlador(GUI_BotonInventario& vista_boton,
		GUI_PanelInventario& vista_inventario);
};

#endif /*__GUI_BOTON_INVENTARIO_CONTROLADOR_H__*/
