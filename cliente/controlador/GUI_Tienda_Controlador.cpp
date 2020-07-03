#include <iostream>

#include "GUI_Tienda_Controlador.h"

GUI_TiendaControlador::GUI_TiendaControlador
(GUI_PanelTienda& vista_tienda,  ServidorProxy& servidor) :
 GUI_PanelControlador(vista_tienda), vista_tienda(vista_tienda),
 servidor(servidor) {}

bool GUI_TiendaControlador::enClick(){
	if(!vista_tienda.activo) return false;

	std::cout << obtenerIndiceClick();
	return true;
}

bool GUI_TiendaControlador::operator()(SDL_Event& evento){
	if(!enRectangulo(rect, evento.button.x, evento.button.y)){
		vista_tienda.activo = false;
		return false;
	}
	return enClick();
}

void GUI_TiendaControlador::actualizarDimension(){
	rect.x = vista_tienda.marco.x;
	rect.y = vista_tienda.marco.y;
	rect.w = SEPARACION + vista_tienda.marco.w*(SEPARACION + LADO_CASILLA);
	rect.h = SEPARACION + vista_tienda.marco.h*(SEPARACION + LADO_CASILLA);
}
