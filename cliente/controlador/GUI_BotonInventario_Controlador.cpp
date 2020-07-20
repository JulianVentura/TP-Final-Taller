#include "GUI_BotonInventario_Controlador.h"
#include "../vista/GUI_BotonInventario.h"


GUI_BotonInventarioControlador::GUI_BotonInventarioControlador
(GUI_BotonInventario& vista_boton, GUI_PanelInventario& vista_inventario)
 : GUI_BotonControlador(vista_boton), vista_inventario(vista_inventario){}

bool GUI_BotonInventarioControlador::enClick(){
	vista_inventario.visible = !vista_inventario.visible;
	return true;
}
