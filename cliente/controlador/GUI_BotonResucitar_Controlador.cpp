#include "GUI_BotonResucitar_Controlador.h"

GUI_BotonResucitarControlador::GUI_BotonResucitarControlador(
	GUI_BotonResucitar& vista, ServidorProxy& servidor)
 : GUI_BotonControlador(vista.x, vista.y, vista.imagen.getAncho(),
  vista.imagen.getAlto()), vista(vista), servidor(servidor){}

bool GUI_BotonResucitarControlador::enClick(){
	servidor.enviarResucitacion();
	return true;
}

void GUI_BotonResucitarControlador::actualizarDimension(){
	rect.x = vista.x;
	rect.y = vista.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}
