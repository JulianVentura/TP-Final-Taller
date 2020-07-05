#include <SDL2/SDL_render.h>

#include "GUI_BotonNuevaCuenta.h"

GUI_BotonNuevaCuenta::GUI_BotonNuevaCuenta(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonNuevaCuenta.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonNuevaCuenta::actualizarDimension(){
	x = ventana->getAncho()*0.1;
	y = ventana->getAlto() - 100;
	imagen.setPosicion(x, y);
}

void GUI_BotonNuevaCuenta::render() {
	imagen.render();
}
