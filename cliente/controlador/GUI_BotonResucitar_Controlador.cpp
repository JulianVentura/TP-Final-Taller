#include "GUI_BotonResucitar_Controlador.h"

GUI_BotonResucitarControlador::GUI_BotonResucitarControlador(
	GUI_BotonResucitar& vista, ServidorProxy& servidor)
 : GUI_BotonControlador(vista), servidor(servidor){}

bool GUI_BotonResucitarControlador::enClick(){
	servidor.enviarResucitacion();
	return true;
}