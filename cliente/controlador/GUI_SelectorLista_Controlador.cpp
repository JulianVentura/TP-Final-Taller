#include "GUI_SelectorLista_Controlador.h"

GUI_SelectorListaControlador::GUI_SelectorListaControlador
(GUI_SelectorLista& vista, std::vector<std::string>& lista) :
GUI_Clickeable({vista.x, vista.y, vista.imagen.getAncho(),
  vista.imagen.getAlto()}), vista(vista), lista(lista){
	i = 0;
	actualizarDimension();
}

bool GUI_SelectorListaControlador::enClick(){
	i++;
	try{
		vista.texto = lista.at(i);
	}catch(const std::out_of_range& e){
		i = 0;
		vista.texto = lista.at(i);
	}

	return true;
}

void GUI_SelectorListaControlador::actualizarDimension(){
	rect.x = vista.x;
	rect.y = vista.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}