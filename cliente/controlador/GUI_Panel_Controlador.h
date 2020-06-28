#ifndef __GUI_PANEL_CONTROLADOR_H__
#define __GUI_PANEL_CONTROLADOR_H__

#include "../vista/GUI_Panel.h"
#include "../vista/GUI_PanelInventario.h"
#include "../controlador/GUI_Boton_Controlador.h"

class GUI_PanelControlador : public GUI_BotonControlador{
protected:
	GUI_Panel& panel;
	int obtenerIndiceClick();
	bool enClick();
public:
	GUI_PanelControlador(GUI_Panel& panel);
};

#endif /*__GUI_PANEL_CONTROLADOR_H__*/