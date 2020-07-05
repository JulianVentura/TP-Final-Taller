#ifndef __GUI_SELECTOR_RAZA_CONTROLADOR_H__
#define __GUI_SELECTOR_RAZA_CONTROLADOR_H__

#include <vector>
#include <string>

#include "GUI_SelectorLista_Controlador.h"

class GUI_SelectorRazaControlador : public GUI_SelectorListaControlador{
private:
	std::vector<std::string> lista;
public:
	explicit GUI_SelectorRazaControlador(GUI_SelectorLista& vista);
};

#endif /*__GUI_SELECTOR_CLASE_H__*/