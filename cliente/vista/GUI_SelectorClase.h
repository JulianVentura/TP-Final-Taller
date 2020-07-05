#ifndef __GUI_SELECTOR_CLASE_H__
#define __GUI_SELECTOR_CLASE_H__

#include "GUI_SelectorLista.h"

class GUI_SelectorClase : public GUI_SelectorLista{
public:
	GUI_SelectorClase(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
};

#endif /*__GUI_SELECTOR_CLASE_H__*/