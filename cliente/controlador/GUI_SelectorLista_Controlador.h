#ifndef __SELECTOR_LISTA_CONTROLADOR_H__
#define __SELECTOR_LISTA_CONTROLADOR_H__

#include <SDL2/SDL_render.h>
#include <vector>
#include <stdexcept>

#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_SelectorLista.h"

class GUI_SelectorListaControlador : public GUI_BotonControlador{
private:
	GUI_SelectorLista& vista;
	std::vector<std::string>& lista;
public:
	int i;
	GUI_SelectorListaControlador(GUI_SelectorLista& vista,
	 std::vector<std::string>& lista);
	bool enClick() override;
	virtual void actualizarDimension();
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/