#include <SDL2/SDL_render.h>

#include "GUI_BotonConectar.h"
#include "../vista/GUI_Login.h"

GUI_BotonConectar::GUI_BotonConectar(EntornoGrafico& entorno,
 Colores& paleta) : imagen(entorno, "assets/botonConectar.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonConectar::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = Y_BASE_LOGIN + 120;
	imagen.setPosicion(x, y);
}

void GUI_BotonConectar::render() {
	imagen.render();
}
