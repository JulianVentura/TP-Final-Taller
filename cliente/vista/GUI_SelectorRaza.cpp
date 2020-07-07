#include "GUI_SelectorRaza.h"

GUI_SelectorRaza::GUI_SelectorRaza(EntornoGrafico& entorno, Colores& paleta):
GUI_SelectorLista(entorno, paleta){}

void GUI_SelectorRaza::actualizarDimension(){
	x = ventana -> getAncho()*0.1;
	y = ventana -> getAlto() - 240;
	GUI_SelectorLista::actualizarDimension();
}