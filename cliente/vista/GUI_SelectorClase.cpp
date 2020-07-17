#include "GUI_SelectorClase.h"
#include "../vista/GUI_Login.h"

GUI_SelectorClase::GUI_SelectorClase(EntornoGrafico& entorno, Colores& paleta):
GUI_SelectorLista(entorno, paleta){}

void GUI_SelectorClase::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = Y_BASE_LOGIN + 160;
	GUI_SelectorLista::actualizarDimension();
}