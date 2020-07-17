#include <string>

#include "GUI_BotonOro.h"
#include "../vista/Ventana.h"

GUI_BotonOro::GUI_BotonOro(EntornoGrafico& entorno, Colores& paleta,
 std::atomic<uint16_t>& oro) : paleta(paleta), oro(oro),
 imagen(entorno, "assets/oro.png") {
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_BotonOro::render(){
	imagen.render();
	renderer -> setColor(paleta.chat_texto);
	int corrimiento_x;
	renderer -> calcularDimensionTexto(std::to_string(oro),
	 &corrimiento_x, NULL);
	renderer -> texto(std::to_string(oro),
	 marco.x + marco.w - corrimiento_x, marco.y - 1);
}

void GUI_BotonOro::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.2 + 4;
	marco.y = ventana_alto - 19; 
	marco.w = 40; marco.h = 15;
	imagen.setPosicion(marco.x - 1, marco.y - 2);
}