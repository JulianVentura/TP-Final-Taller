#ifndef __GUI_TIENDA_CONTROLADOR_H__
#define __GUI_TIENDA_CONTROLADOR_H__

#include "../modelo/ServidorProxy.h"
#include "../controlador/GUI_Panel_Controlador.h"
#include "../vista/GUI_Panel.h"
#include "../vista/GUI_PanelTienda.h"

class GUI_TiendaControlador : public GUI_PanelControlador{
private:
	GUI_PanelTienda& vista_tienda;
	ServidorProxy& servidor;
	bool enClick() override;
public:
	GUI_TiendaControlador(GUI_PanelTienda& vista_tienda,
	 ServidorProxy& servidor);
	bool operator()(SDL_Event& evento) override;
	void actualizarDimension();
};

#endif /*__GUI_TIENDA_CONTROLADOR_H__*/
