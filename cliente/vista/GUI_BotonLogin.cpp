#include <SDL2/SDL_render.h>
#include "../vista/GUI_Login.h"
#include "GUI_BotonLogin.h"

GUI_BotonLogin::GUI_BotonLogin(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonLogin.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonLogin::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = ventana->getAlto() - 90;
	imagen.setPosicion(x, y);
}

void GUI_BotonLogin::render() {
	imagen.render();
}
