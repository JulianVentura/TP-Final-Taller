#include "GUI_BotonOro_Controlador.h"
#include "../vista/GUI_BotonOro.h"


GUI_BotonOroControlador::GUI_BotonOroControlador
(GUI_BotonOro& vista, ServidorProxy& servidor)
 : GUI_BotonControlador(vista), servidor(servidor){}

bool GUI_BotonOroControlador::enClick(){
	switch(SDL_GetMouseState(NULL, NULL)){
		case SDL_BUTTON_LEFT:
		servidor.enviarTransaccion(true);
		break;

		default:
		servidor.enviarTransaccion(false);
		break;
	}

	return true;
}
