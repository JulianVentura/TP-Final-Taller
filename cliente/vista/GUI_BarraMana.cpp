#include "GUI_BarraMana.h"
#include "Ventana.h"

GUI_BarraMana::GUI_BarraMana(EntornoGrafico& entorno, Colores& paleta)
 :  GUI_Barra(entorno, paleta, paleta.barra_mana, paleta.barra_mana2,
  capacidad_max, capacidad){
 	capacidad = 5;
 	capacidad_max = 10;
 	actualizarDimension();
}

void GUI_BarraMana::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.2 + 3*(50 + 4) + 16;
	marco.w = ventana_ancho*0.8 - marco.x - 4;
	marco.y = ventana_alto - 41; marco.h = 8;
}

GUI_BarraMana::~GUI_BarraMana(){}