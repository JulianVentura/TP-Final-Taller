#include "GUI_SelectorRaza_Controlador.h"

GUI_SelectorRazaControlador::GUI_SelectorRazaControlador
(GUI_SelectorLista& vista): GUI_SelectorListaControlador(vista, lista){
	lista.push_back("Humano");
	lista.push_back("Elfo");
	lista.push_back("Enano");
	lista.push_back("Gnomo");
	vista.texto = lista[0];
}