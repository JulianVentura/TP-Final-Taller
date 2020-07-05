#include <SDL2/SDL_render.h>

#include "GUI_BotonConectar.h"

GUI_BotonConectar::GUI_BotonConectar(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonConectar.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonConectar::actualizarDimension(){
	x =  ventana->getAncho()*0.1;
	y =  ventana->getAlto()*0.2 + 110;
	imagen.setPosicion(x, y);
}

void GUI_BotonConectar::render() {
	imagen.render();
}
