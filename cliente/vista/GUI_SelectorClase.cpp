#include "GUI_SelectorClase.h"

GUI_SelectorClase::GUI_SelectorClase(EntornoGrafico& entorno, Colores& paleta):
GUI_SelectorLista(entorno, paleta){}

void GUI_SelectorClase::actualizarDimension(){
	x = ventana -> getAncho()*0.1;
	y = ventana -> getAlto() - 200;
	GUI_SelectorLista::actualizarDimension();
}