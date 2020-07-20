#include "GUI_BotonMeditar_Controlador.h"

GUI_BotonMeditarControlador::GUI_BotonMeditarControlador(
	GUI_BotonMeditar& vista, ServidorProxy& servidor)
 : GUI_BotonControlador(vista), servidor(servidor){}

bool GUI_BotonMeditarControlador::enClick(){
	servidor.enviarMeditacion();
	return true;
}
