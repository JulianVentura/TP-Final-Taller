#include "GUI_BarraVida.h"
#include "Ventana.h"

GUI_BarraVida::GUI_BarraVida(EntornoGrafico& entorno, Colores& paleta)
 :  GUI_Barra(entorno, paleta.vida, capacidad_max, capacidad){
 	capacidad = 4;
 	capacidad_max = 10;
 	actualizar_dimension();
}

void GUI_BarraVida::actualizar_dimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.4; marco.y = ventana_alto - 8 - 16;
	marco.w = ventana_ancho*0.3; marco.h = 16;
}

GUI_BarraVida::~GUI_BarraVida(){}