#include "GUI_BotonResucitar.h"

GUI_BotonResucitar::GUI_BotonResucitar(EntornoGrafico& entorno,
 Colores& paleta) : GUI_Boton(entorno, "assets/gui/botonResucitar.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonResucitar::actualizarDimension(){
	x = ventana->getAncho()*0.8 - 4 - imagen.getAncho();
	y =  ventana->getAlto() - imagen.getAlto() - 10;
	imagen.setPosicion(x, y);
}
