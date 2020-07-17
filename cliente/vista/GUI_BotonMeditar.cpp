#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonMeditar.h"
#include "Ventana.h"

GUI_BotonMeditar::GUI_BotonMeditar(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonMeditar.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonMeditar::actualizarDimension(){
	x = ventana->getAncho()*0.8 - 35 - imagen.getAncho()/2;
	y =  ventana->getAlto() - imagen.getAlto() - 15;
	imagen.setPosicion(x, y);
}

void GUI_BotonMeditar::render() {
	imagen.render();
}