#ifndef __GUI_PRINCIPAL_H__
#define __GUI_PRINCIPAL_H__

#include <SDL2/SDL_render.h>
#include <vector>
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "GUI_BotonInventario.h"
#include "../modelo/BuclePrincipal.h"
#include "../controlador/GUI_BotonInventario_Controlador.h"


class GUI_Principal : public IRendereable {
private:
	Barra *barra_vida, *barra_mana, *barra_exp;
	GUI_BotonInventarioControlador *inventario_controlador;
	GUI_BotonInventario *inventario_vista;
public:
	GUI_Principal(EntornoGrafico& entorno, BuclePrincipal& bucle);
	~GUI_Principal();
	void render() override;
};

#endif /*__GUI_PRINCIPAL_H__*/
