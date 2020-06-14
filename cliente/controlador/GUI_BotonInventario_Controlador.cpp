#include "GUI_BotonInventario_Controlador.h"
#include "../vista/GUI_BotonInventario.h"

GUI_BotonInventarioControlador::GUI_BotonInventarioControlador
(GUI_BotonInventario& vista, int x, int y, int ancho, int largo)
 : GUI_BotonControlador(x, y, ancho, largo), vista(vista){}

bool GUI_BotonInventarioControlador::enClick(){
	vista.visible = !vista.visible;
	return true;
}
