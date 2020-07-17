#include <SDL2/SDL_render.h>

#include "GUI_BotonNuevaCuenta.h"
#include "../vista/GUI_Login.h"

GUI_BotonNuevaCuenta::GUI_BotonNuevaCuenta(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonNuevaCuenta.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonNuevaCuenta::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = ventana->getAlto() - 45;
	imagen.setPosicion(x, y);
}

void GUI_BotonNuevaCuenta::render() {
	imagen.render();
}
