#include <vector>

#include "GUI_Principal.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

#include "../modelo/BuclePrincipal.h"

GUI_Principal::GUI_Principal(EntornoGrafico& entorno, Colores& paleta,
	DatosPersonaje& datos_personaje, DatosTienda& datos_tienda) :
	dock(entorno, paleta),
	barra_vida(entorno, paleta, datos_personaje.vida_max, datos_personaje.vida),
	barra_mana(entorno, paleta, datos_personaje.mana_max, datos_personaje.mana),
	barra_exp(entorno, paleta, datos_personaje.exp_max, datos_personaje.exp),
	imagenes_equipo(entorno),
	inventario_vista(entorno, paleta, imagenes_equipo,
	 datos_personaje.inventario, datos_personaje.equipados),
	boton_oro_vista(entorno, paleta, datos_personaje.oro),
	boton_inventario_vista(entorno, paleta),
	boton_meditar_vista(entorno, paleta),
	tienda_vista(entorno, paleta, imagenes_equipo, datos_tienda.inventario,
	 datos_tienda.precios, datos_tienda.activo),
	chat_vista(entorno, paleta),
	nivel_vista(entorno, paleta, datos_personaje.nivel){
	entorno.agregarRendereable(this);
}

void GUI_Principal::actualizar(unsigned int delta_t) {
	chat_vista.actualizar(delta_t);
}

void GUI_Principal::render() {
	barra_exp.render();
	dock.render();
	barra_vida.render();
	barra_mana.render();
	chat_vista.render();
	boton_inventario_vista.render();
	boton_meditar_vista.render();
	inventario_vista.render();
	tienda_vista.render();
	boton_oro_vista.render();
	nivel_vista.render();
}

void GUI_Principal::actualizarDimension(){
	dock.actualizarDimension();
	barra_exp.actualizarDimension();
	barra_vida.actualizarDimension();
	barra_mana.actualizarDimension();
	boton_inventario_vista.actualizarDimension();
	boton_meditar_vista.actualizarDimension();
	inventario_vista.actualizarDimension();
	tienda_vista.actualizarDimension();
	boton_oro_vista.actualizarDimension();
	chat_vista.actualizarDimension();
	nivel_vista.actualizarDimension();
}

GUI_Principal::~GUI_Principal(){}
