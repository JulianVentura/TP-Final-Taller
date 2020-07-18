#include "GUI_OroAlmacenado.h"

GUI_OroAlmacenado::GUI_OroAlmacenado(EntornoGrafico& entorno, Colores& paleta,
	 std::atomic<uint32_t>& oro)
	: GUI_BotonOro(entorno, paleta, oro), oro(oro){
	marco.w = 40; marco.h = 15;
}

void GUI_OroAlmacenado::actualizarDimension(){
	marco.x = ventana->getAncho()*0.8 - (marco.w)*(SEPARACION + LADO_CASILLA)
	 + (marco.w/2)*(SEPARACION + LADO_CASILLA) + 40;
	marco.y = ventana->getAlto()*0.9 - marco.h*(SEPARACION + LADO_CASILLA)
	 - 4*SEPARACION - imagen.getAlto();
	imagen.setPosicion(marco.x - 1, marco.y - 2);
}

void GUI_OroAlmacenado::render(){
	if(oro == 0) return;
	GUI_BotonOro::render();
}