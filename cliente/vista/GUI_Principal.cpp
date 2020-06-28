#include <vector>

#include "GUI_Principal.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

#include "../modelo/BuclePrincipal.h"

GUI_Principal::GUI_Principal(EntornoGrafico& entorno, Colores& paleta,
	DatosPersonaje& datos_personaje) :
	dock(entorno, paleta),
	barra_vida(entorno, paleta, datos_personaje.vida_max, datos_personaje.vida),
	barra_mana(entorno, paleta, datos_personaje.mana_max, datos_personaje.mana),
	barra_exp(entorno, paleta, datos_personaje.exp_max, datos_personaje.exp),
	oro(entorno, paleta, datos_personaje.oro),
	imagenes_equipo(entorno),
	inventario_vista(entorno, paleta, imagenes_equipo,
	 datos_personaje.inventario),
	inventario_controlador(inventario_vista),
	boton_inventario_vista(entorno, paleta),
	boton_inventario_controlador(boton_inventario_vista, inventario_vista),
	chat_vista(entorno, paleta),
	chat_controlador(chat_vista){
	entorno.agregarRendereable(this);

	botones.push_back(&boton_inventario_controlador);
	botones.push_back(&inventario_controlador);
	botones.push_back(&chat_controlador);

}

void GUI_Principal::render() {
	barra_exp.render();
	dock.render();
	barra_vida.render();
	barra_mana.render();
	chat_vista.render();
	boton_inventario_vista.render();
	inventario_vista.render();
	oro.render();
}

void GUI_Principal::actualizarDimension(){
	dock.actualizarDimension();
	barra_exp.actualizarDimension();
	barra_vida.actualizarDimension();
	barra_mana.actualizarDimension();
	boton_inventario_vista.actualizarDimension();
	inventario_vista.actualizarDimension();
	oro.actualizarDimension();
	chat_vista.actualizarDimension();
	boton_inventario_controlador.actualizarDimension();
	inventario_controlador.actualizarDimension();
	chat_controlador.actualizarDimension();
}

GUI_Principal::~GUI_Principal(){}
