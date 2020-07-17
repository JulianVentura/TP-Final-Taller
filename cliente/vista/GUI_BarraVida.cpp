#include "GUI_BarraVida.h"
#include "Ventana.h"

GUI_BarraVida::GUI_BarraVida(EntornoGrafico& entorno, Colores& paleta,
	  std::atomic<uint16_t>& vida_max , std::atomic<uint16_t>& vida)
 :  GUI_Barra(entorno, paleta, paleta.barra_vida, paleta.barra_vida2,
  vida_max, vida){
 	actualizarDimension();
}

void GUI_BarraVida::actualizarDimension(){
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();
	marco.x = ventana_ancho*0.2 + 70;
	marco.w = ventana_ancho*0.8 - marco.x - 75;
	marco.y = ventana_alto - 25;  marco.h = 16;
}

GUI_BarraVida::~GUI_BarraVida(){}
