#include <vector>

#include "GUI_Principal.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

#include "../modelo/BuclePrincipal.h"

GUI_Principal::GUI_Principal(EntornoGrafico& entorno, Colores& paleta) :
	dock(entorno, paleta),
	barra_vida(entorno, paleta),
	barra_mana(entorno, paleta),
	barra_exp(entorno, paleta),
	oro(entorno, paleta),
	inventario_vista(entorno, paleta),
	inventario_controlador(inventario_vista),
	chat_vista(entorno, paleta),
	chat_controlador(chat_vista){
	entorno.agregarRendereable(this);

	oro.oro = 0;

	botones.push_back(&inventario_controlador);
	botones.push_back(&chat_controlador);

	chat_vista.agregarMensaje("Hola");
	chat_vista.agregarMensaje("Hola, todo bien? :)");
}

void GUI_Principal::render() {
	oro.oro += 1;
	barra_exp.render();
	dock.render();
	barra_vida.render();
	barra_mana.render();
	inventario_vista.render();
	oro.render();
	chat_vista.render();
}

void GUI_Principal::actualizarDimension(){
	dock.actualizarDimension();
	barra_exp.actualizarDimension();
	barra_vida.actualizarDimension();
	barra_mana.actualizarDimension();
	inventario_vista.actualizarDimension();
	oro.actualizarDimension();
	chat_vista.actualizarDimension();
	inventario_controlador.actualizarDimension();
	chat_controlador.actualizarDimension();
}

GUI_Principal::~GUI_Principal(){}
