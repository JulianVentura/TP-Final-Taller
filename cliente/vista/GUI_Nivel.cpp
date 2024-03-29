#include "GUI_Nivel.h"

GUI_Nivel::GUI_Nivel(EntornoGrafico& entorno, Colores& paleta,
std::atomic<uint16_t>& nivel) : nivel(nivel), paleta(paleta),
	imagen(entorno, "assets/gui/nivel.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_Nivel::render(){
	imagen.render();
	renderer -> setColor(paleta.oro);
	renderer -> textoAIzq(std::to_string(nivel), x , y);
}

void GUI_Nivel::actualizarDimension(){
	x = ventana->getAncho()*0.8 + 4 - imagen.getAncho()/2;
	y =  ventana->getAlto() - 50 - imagen.getAlto()/2;
	imagen.setPosicion(x, y);
	x += (imagen.getAncho()*3)/4;
	y += imagen.getAlto()/2;
}