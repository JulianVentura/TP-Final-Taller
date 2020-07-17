#include "GUI_BotonOro_Controlador.h"
#include "../vista/GUI_BotonOro.h"


GUI_BotonOroControlador::GUI_BotonOroControlador
(GUI_BotonOro& vista, ServidorProxy& servidor)
 : GUI_BotonControlador(vista.marco.x, vista.marco.y,
  vista.imagen.getAncho(), vista.imagen.getAlto()),
  vista(vista), servidor(servidor){}

bool GUI_BotonOroControlador::enClick(){
	switch(SDL_GetMouseState(NULL, NULL)){
		case SDL_BUTTON_LEFT:
		//servidor.enviarUtilizar(obtenerIndiceClick());
		break;

		default:
		//servidor.enviarTirar(obtenerIndiceClick());
		break;
	}

	return true;
}

void GUI_BotonOroControlador::actualizarDimension(){
	rect.x = vista.marco.x;
	rect.y = vista.marco.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}
