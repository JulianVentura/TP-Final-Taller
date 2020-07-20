#include "GUI_Boton.h"

GUI_Boton::GUI_Boton(EntornoGrafico& entorno, std::string ruta) :
imagen(entorno, ruta.c_str()){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_Boton::render(){
	imagen.render();
}

void GUI_Boton::actualizarDimension(){}

SDL_Rect GUI_Boton::obtenerMarco(){
	SDL_Rect marco = {x, y , imagen.getAncho(), imagen.getAlto()};
	return marco;
}