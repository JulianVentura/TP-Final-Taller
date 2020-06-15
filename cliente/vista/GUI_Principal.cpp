#include <vector>

#include "GUI_Principal.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

GUI_Principal::GUI_Principal(EntornoGrafico& entorno) {
	entorno.agregarRendereable(this);
	SDL_Rect marco;
	SDL_Color color;
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();

	color.r = 120; color.g = 40; color.b = 0; color.a = 255;
	marco.x = ventana_ancho*0.7; marco.y = ventana_alto*0.9 - 5;
	marco.w = ventana_ancho*0.3; marco.h = 12;
	barra_vida = new Barra(entorno, marco, color, 10, 1);
	
	color.r = 20; color.g = 20; color.b = 120; color.a = 255;
	marco.y = ventana_alto*0.9 - 10 - 12; marco.h = 6;
	barra_mana = new Barra(entorno, marco, color, 10, 8);
}

void GUI_Principal::render() {
	// SDL_Rect marco;
	barra_mana->render();
	barra_vida->render();
}

GUI_Principal::~GUI_Principal(){
	delete barra_vida;
	//delete barra_mana;
}