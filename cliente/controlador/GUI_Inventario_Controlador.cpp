#include "GUI_Inventario_Controlador.h"

bool GUI_InventarioControlador::enClick(){
	if(!vista_inventario.visible) return false;
	std::string a = "Comerciante";

	switch(SDL_GetMouseState(NULL, NULL)){
		case SDL_BUTTON_LEFT:
		
		servidor.enviarInteraccion(a);

		//servidor.enviarUtilizar(obtenerIndiceClick());
		break;

		case SDL_BUTTON_RIGHT:
		servidor.enviarTirar(obtenerIndiceClick());
		break;
	}
	return true;
}

GUI_InventarioControlador::GUI_InventarioControlador
(GUI_PanelInventario& vista_inventario, ServidorProxy& servidor) :
 GUI_PanelControlador(vista_inventario), vista_inventario(vista_inventario), 
 servidor(servidor){}

void GUI_InventarioControlador::actualizarDimension(){
	rect.x = vista_inventario.marco.x;
	rect.y = vista_inventario.marco.y;
	rect.w = SEPARACION + vista_inventario.marco.w*(SEPARACION + LADO_CASILLA);
	rect.h = SEPARACION + vista_inventario.marco.h*(SEPARACION + LADO_CASILLA);
}
