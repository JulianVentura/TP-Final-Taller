#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonInventario.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno, int x, int y)
: imagen(entorno,"assets/botonInventario.png"){
	imagen.setPosicion(x,y);
	visible = false;
}

void GUI_BotonInventario::render(){
	imagen.render();
	if(!visible) return;
	renderer -> setColor(0,0,0,255);
	renderer -> rectSolido(50,50,200,200);
}
