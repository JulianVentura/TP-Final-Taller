#include <vector>

#include "GUI_Principal.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

#include "../modelo/BuclePrincipal.h"

GUI_Principal::GUI_Principal(EntornoGrafico& entorno, BuclePrincipal& bucle
	, Colores& paleta) :
	dock(entorno, paleta),
	barra_vida(entorno, paleta),
	barra_mana(entorno, paleta),
	barra_exp(entorno, paleta),
	oro(entorno, paleta),
	chat_vista(entorno, paleta),
	chat_controlador(chat_vista){
	oro.oro = 0;
	entorno.agregarRendereable(this);
	inventario_vista = new GUI_BotonInventario(entorno, paleta,
	 ventana->getAncho()*0.2 + 4, ventana->getAlto() - 50);
	inventario_controlador = new GUI_BotonInventarioControlador(
		*inventario_vista, ventana->getAncho()*0.2 + 4, ventana->getAlto() - 50,
		 50, 50);
	bucle.botones.push_back(inventario_controlador);

	bucle.chat = &chat_controlador;
	bucle.botones.push_back(&chat_controlador);

	chat_vista.agregarMensaje("Hola");
	chat_vista.agregarMensaje("Hola, todo bien? :)");
}

void GUI_Principal::render() {
	oro.oro += 1;
	barra_exp.render();
	dock.render();
	barra_vida.render();
	barra_mana.render();
	inventario_vista -> render();
	oro.render();
	chat_vista.render();
}

GUI_Principal::~GUI_Principal(){
	delete inventario_vista;
	delete inventario_controlador;
}
