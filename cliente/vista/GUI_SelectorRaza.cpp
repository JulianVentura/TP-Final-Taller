#include "GUI_SelectorRaza.h"
#include "../vista/GUI_Login.h"

GUI_SelectorRaza::GUI_SelectorRaza(EntornoGrafico& entorno, Colores& paleta):
GUI_SelectorLista(entorno, paleta){}

void GUI_SelectorRaza::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = Y_BASE_LOGIN + 120;
	GUI_SelectorLista::actualizarDimension();
}