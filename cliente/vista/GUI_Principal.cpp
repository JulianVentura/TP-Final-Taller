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
	barra_exp(entorno, paleta)
{
	entorno.agregarRendereable(this);
	inventario_vista = new GUI_BotonInventario(entorno, paleta,
	 ventana->getAncho()*0.2 + 4, ventana->getAlto() - 50);
	inventario_controlador = new GUI_BotonInventarioControlador(
		*inventario_vista, ventana->getAncho()*0.2 + 4, ventana->getAlto() - 50,
		 50, 50);
	bucle.botones.push_back(inventario_controlador);
}

void GUI_Principal::render() {
	dock.render();
	barra_vida.render();
	barra_mana.render();
	barra_exp.render();
	inventario_vista -> render();
}

GUI_Principal::~GUI_Principal(){
	delete inventario_vista;
	delete inventario_controlador;
}