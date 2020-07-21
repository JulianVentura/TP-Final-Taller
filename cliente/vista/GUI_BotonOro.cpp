#include <string>

#include "GUI_BotonOro.h"
#include "../vista/Ventana.h"

GUI_BotonOro::GUI_BotonOro(EntornoGrafico& entorno, Colores& paleta,
 std::atomic<uint16_t>& oro) : GUI_Boton(entorno, "assets/gui/oro.png"),
paleta(paleta), oro(oro){}

void GUI_BotonOro::render(){
	imagen.render();
	renderer -> setColor(paleta.oro);
	renderer -> textoAIzq(std::to_string(oro), marco.x + marco.w, marco.y - 1);
}

void GUI_BotonOro::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	x = ventana_ancho*0.2 + 4;
	y = ventana_alto - 19; 
	marco.x = x; marco.y = y;
	marco.w = 40; marco.h = 15;
	imagen.setPosicion(marco.x - 1, marco.y - 2);
}
