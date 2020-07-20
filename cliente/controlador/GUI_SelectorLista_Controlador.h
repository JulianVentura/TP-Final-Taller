#ifndef __SELECTOR_LISTA_CONTROLADOR_H__
#define __SELECTOR_LISTA_CONTROLADOR_H__

#include <SDL2/SDL_render.h>
#include <vector>
#include <stdexcept>

#include "../controlador/GUI_Clickeable.h"
#include "../vista/GUI_SelectorLista.h"


class GUI_SelectorListaControlador : public GUI_Clickeable{
private:
	int i;
	GUI_SelectorLista& vista;
	std::vector<std::string>& lista;
public:
	GUI_SelectorListaControlador(GUI_SelectorLista& vista,
	 std::vector<std::string>& lista);

	// Realiza una iteración circular por los elementos de "lista"
	// y actualiza la salida de "vista".
	bool enClick() override;

	virtual void actualizarDimension();
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/