#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonResucitar.h"
#include "Ventana.h"

GUI_BotonResucitar::GUI_BotonResucitar(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonResucitar.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonResucitar::actualizarDimension(){
	x = ventana->getAncho()*0.8 - 4 - imagen.getAncho();
	y =  ventana->getAlto() - imagen.getAlto() - 10;
	imagen.setPosicion(x, y);
}

void GUI_BotonResucitar::render() {
	imagen.render();
}