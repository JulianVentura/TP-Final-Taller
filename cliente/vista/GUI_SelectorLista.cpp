#include "GUI_SelectorLista.h"

GUI_SelectorLista::GUI_SelectorLista(EntornoGrafico& entorno, Colores& paleta):
paleta(paleta), imagen(entorno, "assets/gui/botonVacio.png"){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_SelectorLista::actualizarDimension(){
	imagen.setPosicion(x, y);
}

void GUI_SelectorLista::render(){
	imagen.render();
	int corrimiento_x;
	renderer -> setColor(paleta.login_texto);
	renderer -> calcularDimensionTexto(texto, &corrimiento_x, NULL);
	renderer -> texto(texto, x + (imagen.getAncho() - corrimiento_x)/2 , y + 5);
}