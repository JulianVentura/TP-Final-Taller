#include <vector>

#include "GUI_Principal.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

#include "../modelo/BuclePrincipal.h"

GUI_Principal::GUI_Principal(EntornoGrafico& entorno, BuclePrincipal& bucle) {
	entorno.agregarRendereable(this);
	SDL_Rect marco;
	SDL_Color color;
	int ventana_ancho = ventana->getAncho();
	int ventana_alto  = ventana->getAlto();

	color.r = 120; color.g = 40; color.b = 0; color.a = 255;
	marco.x = ventana_ancho*0.4; marco.y = ventana_alto - 8 - 16;
	marco.w = ventana_ancho*0.3; marco.h = 16;
	barra_vida = new Barra(entorno, marco, color, 10, 1);
	
	color.r = 20; color.g = 20; color.b = 120; color.a = 255;
	marco.y = ventana_alto - 28 - 8; marco.h = 8;
	barra_mana = new Barra(entorno, marco, color, 10, 8);

	color.r = 171; color.g = 169; color.b = 90; color.a = 255;
	marco.w = ventana->getAncho()*0.6; marco.h = 6;
	marco.x = ventana->getAncho()*0.2; marco.y = ventana->getAlto()*0.9 - 6;
	barra_exp = new Barra(entorno, marco, color, 10, 8);

	inventario_vista = new GUI_BotonInventario(entorno, ventana->getAncho()*0.2
	 + 4, ventana->getAlto() - 50);
	inventario_controlador = new GUI_BotonInventarioControlador(
		*inventario_vista, ventana->getAncho()*0.2 + 4, ventana->getAlto() - 50,
		 50, 50);
	bucle.botones.push_back(inventario_controlador);
}

void GUI_Principal::render() {
	renderer -> setColor(80,57,37,255);
	renderer -> rectSolido(ventana->getAncho()*0.2,ventana->getAlto()*0.9
		,ventana->getAncho()*0.6,ventana->getAlto()*0.1);
	renderer -> setColor(94,75,51,255);
	renderer -> rectSolido(ventana->getAncho()*0.2,ventana->getAlto()*0.9
		,ventana->getAncho()*0.6,ventana->getAlto()*0.005);
	inventario_vista -> render();
	barra_mana->render();
	barra_vida->render();
	barra_exp -> render();
}

GUI_Principal::~GUI_Principal(){
	delete barra_vida;
	delete barra_mana;
	delete barra_exp;
	delete inventario_vista;
	delete inventario_controlador;
}