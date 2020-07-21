#ifndef __GUI_INVENTARIO_CONTROLADOR_H__
#define __GUI_INVENTARIO_CONTROLADOR_H__

#include "../modelo/ServidorProxy.h"
#include "../controlador/GUI_Panel_Controlador.h"
#include "../vista/GUI_Panel.h"
#include "../vista/GUI_PanelInventario.h"

class GUI_InventarioControlador : public GUI_PanelControlador{
private:
	GUI_PanelInventario& vista_inventario;
	ServidorProxy& servidor;

	//Envía las operaciones tirar, vender o utilizar.
	bool enClick();
public:
	GUI_InventarioControlador(GUI_PanelInventario& vista_inventario,
		 ServidorProxy& servidor);
	void actualizarDimension();
};

#endif /*__GUI_INVENTARIO_CONTROLADOR_H__*/
