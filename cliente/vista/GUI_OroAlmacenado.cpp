#include "GUI_OroAlmacenado.h"
#include "../modelo/DatosPersonaje.h"

GUI_OroAlmacenado::GUI_OroAlmacenado(EntornoGrafico& entorno, Colores& paleta,
	std::atomic<uint16_t>& oro) : paleta(paleta), oro(oro),
	imagen(entorno, "assets/gui/oroAlmacen.png"){
	entorno.agregarRendereable(this);
	marco.w = 40; marco.h = 15;
	actualizarDimension();
}

void GUI_OroAlmacenado::actualizarDimension(){
	marco.x = ventana->getAncho()*0.8;
	marco.y = ventana->getAlto()*0.9 - INV_ALTO*(SEPARACION + LADO_CASILLA)
	 - 4*SEPARACION - imagen.getAlto();
	imagen.setPosicion(marco.x, marco.y);
}

void GUI_OroAlmacenado::render(){
	if(oro == 0) return;
	imagen.render();
	renderer -> setColor(paleta.oro);
	renderer -> textoAIzq(std::to_string(oro), marco.x + marco.w, marco.y - 1);
}