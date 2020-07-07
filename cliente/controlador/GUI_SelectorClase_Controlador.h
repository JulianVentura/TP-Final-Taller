#ifndef __GUI_SELECTOR_CLASE_CONTROLADOR_H__
#define __GUI_SELECTOR_CLASE_CONTROLADOR_H__

#include <vector>
#include <string>

#include "GUI_SelectorLista_Controlador.h"

class GUI_SelectorClaseControlador : public GUI_SelectorListaControlador{
private:
	std::vector<std::string> lista;
public:
	explicit GUI_SelectorClaseControlador(GUI_SelectorLista& vista);
};

#endif /*__GUI_SELECTOR_CLASE_H__*/