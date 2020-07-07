#include "GUI_BarraExp.h"
#include "Ventana.h"

GUI_BarraExp::GUI_BarraExp(EntornoGrafico& entorno, Colores& paleta,
	std::atomic<uint16_t>& exp_max , std::atomic<uint16_t>& exp) : GUI_Barra(entorno,
	 paleta, paleta.barra_exp, paleta.barra_exp2, exp_max, exp){
 	actualizarDimension();
}

void GUI_BarraExp::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.w = ventana_ancho*0.6; marco.h = 6;
	marco.x = ventana_ancho*0.2; marco.y = ventana_alto - 50 - marco.h;
}

GUI_BarraExp::~GUI_BarraExp(){}
