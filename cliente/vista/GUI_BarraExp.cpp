#include "GUI_BarraExp.h"
#include "Ventana.h"

GUI_BarraExp::GUI_BarraExp(EntornoGrafico& entorno, Colores& paleta)
 :  GUI_Barra(entorno, paleta, paleta.barra_exp, paleta.barra_exp2,
  capacidad_max, capacidad){
 	capacidad = 9;
 	capacidad_max = 10;
 	actualizar_dimension();
}

void GUI_BarraExp::actualizar_dimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.w = ventana_ancho*0.6; marco.h = 6;
	marco.x = ventana_ancho*0.2; marco.y = ventana_alto - 50 - marco.h;
}

GUI_BarraExp::~GUI_BarraExp(){}