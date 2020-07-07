#include "GUI_SelectorClase_Controlador.h"

GUI_SelectorClaseControlador::GUI_SelectorClaseControlador
(GUI_SelectorLista& vista): GUI_SelectorListaControlador(vista, lista){
	lista.push_back("Mago");
	lista.push_back("Clerigo");
	lista.push_back("Paladin");
	lista.push_back("Guerrero");
	vista.texto = lista[0];
}