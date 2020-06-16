#include "GUI_BarraMana.h"
#include "Ventana.h"

GUI_BarraMana::GUI_BarraMana(EntornoGrafico& entorno, Colores& paleta)
 :  GUI_Barra(entorno, paleta.mana, capacidad_max, capacidad){
 	capacidad = 5;
 	capacidad_max = 10;
 	actualizar_dimension();
}

void GUI_BarraMana::actualizar_dimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.4; marco.y = ventana_alto - 28 - 8;
	marco.w = ventana_ancho*0.3; marco.h = 8;
}

GUI_BarraMana::~GUI_BarraMana(){}