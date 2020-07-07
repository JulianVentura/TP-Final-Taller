#include <SDL2/SDL_render.h>

#include "GUI_BotonLogin.h"

GUI_BotonLogin::GUI_BotonLogin(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonLogin.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonLogin::actualizarDimension(){
	x = ventana->getAncho()*0.1;
	y = ventana->getAlto() - 140;

	imagen.setPosicion(x, y);
}

void GUI_BotonLogin::render() {
	imagen.render();
}
