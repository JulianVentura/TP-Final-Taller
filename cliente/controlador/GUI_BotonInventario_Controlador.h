#ifndef __GUI_BOTON_INVENTARIO_CONTROLADOR_H__
#define __GUI_BOTON_INVENTARIO_CONTROLADOR_H__

#include "GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonInventario.h"

#define ALTO_INVENTARIO  5
#define ANCHO_INVENTARIO 3

class GUI_BotonInventarioControlador : public GUI_BotonControlador{
private:
	char inventario[ANCHO_INVENTARIO][ALTO_INVENTARIO];
	GUI_BotonInventario& inventario_vista;
	bool enClick();
public:
	void actualizarDimension();
	GUI_BotonInventarioControlador(GUI_BotonInventario& vista);
};

#endif /*__GUI_BOTON_INVENTARIO_CONTROLADOR_H__*/
