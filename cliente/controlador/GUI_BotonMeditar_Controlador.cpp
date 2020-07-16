#include "GUI_BotonMeditar_Controlador.h"

GUI_BotonMeditarControlador::GUI_BotonMeditarControlador(
	GUI_BotonMeditar& vista, ServidorProxy& servidor)
 : GUI_BotonControlador(vista.x, vista.y, vista.imagen.getAncho(),
  vista.imagen.getAlto()), vista(vista), servidor(servidor){}

bool GUI_BotonMeditarControlador::enClick(){
	servidor.enviarMeditacion();
	return true;
}

void GUI_BotonMeditarControlador::actualizarDimension(){
	rect.x = vista.x;
	rect.y = vista.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}
