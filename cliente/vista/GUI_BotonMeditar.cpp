#include "GUI_BotonMeditar.h"

GUI_BotonMeditar::GUI_BotonMeditar(EntornoGrafico& entorno,
 Colores& paleta) : GUI_Boton(entorno, "assets/gui/botonMeditar.png"){}

void GUI_BotonMeditar::actualizarDimension(){
	x = ventana->getAncho()*0.8 - 8 - 2*imagen.getAncho();
	y =  ventana->getAlto() - imagen.getAlto() - 10;
	imagen.setPosicion(x, y);
}