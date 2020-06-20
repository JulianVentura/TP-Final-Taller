#include <string>

#include "GUI_Oro.h"
#include "../vista/Ventana.h"

GUI_Oro::GUI_Oro(EntornoGrafico& entorno, Colores& paleta) : paleta(paleta) {
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_Oro::render(){
	renderer -> setColor(paleta.barra_fondo);
	renderer -> rectSolido(marco);
	renderer -> setColor(paleta.inv_frente);
	renderer -> rect(marco);
	renderer -> setColor(255,255,255,125);
	renderer -> texto(std::to_string(oro), marco.x, marco.y);
}

void GUI_Oro::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.2 + 4;
	marco.y = ventana_alto - 19; 
	marco.w = 40; marco.h = 15;
}
