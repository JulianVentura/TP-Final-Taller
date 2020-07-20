#include "../vista/GUI_BotonInventario.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno,
 Colores& paleta) : GUI_Boton(entorno, "assets/gui/botonInventario.png"){}

void GUI_BotonInventario::actualizarDimension(){
	x = ventana->getAncho()*0.2 + 4;
	y =  ventana->getAlto() - imagen.getAlto() - 20;
	imagen.setPosicion(x, y);
}
