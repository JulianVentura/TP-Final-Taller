#ifndef __SELECTOR_LISTA_H__
#define __SELECTOR_LISTA_H__

#include <string>

#include "../vista/Ventana.h"
#include "../vista/IRendereable.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"

class GUI_SelectorLista : public IRendereable{
private:
	
	Colores& paleta;
public:
	int x,y;
	Imagen imagen;
	std::string texto;
	GUI_SelectorLista(EntornoGrafico& entorno, Colores& paleta);
	void render();
	void actualizarDimension();
};

#endif /*__SELECTOR_LISTA_H__*/
