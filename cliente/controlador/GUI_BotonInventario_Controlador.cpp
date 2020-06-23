#include "GUI_BotonInventario_Controlador.h"
#include "../vista/GUI_BotonInventario.h"

GUI_BotonInventarioControlador::GUI_BotonInventarioControlador
(GUI_BotonInventario& vista)
 : GUI_BotonControlador(vista.x, vista.y, LADO_CASILLA, LADO_CASILLA),
  inventario_vista(vista){}

bool GUI_BotonInventarioControlador::enClick(){
	inventario_vista.visible = !inventario_vista.visible;
	return true;
}

void GUI_BotonInventarioControlador::actualizarDimension(){
	rect.x = inventario_vista.x;
	rect.y = inventario_vista.y;
}