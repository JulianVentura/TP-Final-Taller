#include <string>

#include "GUI_Oro.h"
#include "../vista/Ventana.h"

GUI_Oro::GUI_Oro(EntornoGrafico& entorno, Colores& paleta,
 std::atomic<int>& oro) : imagen(entorno, "assets/oro.png"),
  paleta(paleta), oro(oro) {
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_Oro::render(){
	renderer -> setColor(paleta.barra_fondo);
	renderer -> rectSolido(marco);
	renderer -> setColor(paleta.inv_frente);
	renderer -> rect(marco);
	renderer -> setColor(255,255,255,125);

	int corrimiento_x;
	renderer -> calcularDimensionTexto(std::to_string(oro),
	 &corrimiento_x, NULL);
	renderer -> texto(std::to_string(oro),
	 marco.x + marco.w - corrimiento_x, marco.y - 1);
	imagen.render();
}

void GUI_Oro::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.2 + 4;
	marco.y = ventana_alto - 19; 
	marco.w = 40; marco.h = 15;
	imagen.setPosicion(marco.x + marco.w + 1, marco.y - 1);
}
