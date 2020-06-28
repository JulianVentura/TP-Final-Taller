#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonInventario.h"
#include "Ventana.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonInventario.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonInventario::actualizarDimension(){
	x = ventana->getAncho()*0.2 + 4;
	y =  ventana->getAlto() - imagen.getAlto() - 10;
	imagen.setPosicion(x, y);
}

void GUI_BotonInventario::render() {
	imagen.render();
}
