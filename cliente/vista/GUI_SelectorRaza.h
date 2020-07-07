#ifndef __GUI_SELECTOR_RAZA_H__
#define __GUI_SELECTOR_RAZA_H__

#include "GUI_SelectorLista.h"

class GUI_SelectorRaza : public GUI_SelectorLista{
public:
	GUI_SelectorRaza(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
};

#endif /*__GUI_SELECTOR_CLASE_H__*/