#ifndef __GUI_PANEL_CONTROLADOR_H__
#define __GUI_PANEL_CONTROLADOR_H__

#include "../vista/GUI_Panel.h"
#include "../vista/GUI_PanelInventario.h"
#include "../controlador/GUI_Clickeable.h"

class GUI_PanelControlador : public GUI_Clickeable{
protected:
	GUI_Panel& panel;
	int obtenerIndiceClick();
	bool enClick();
public:
	explicit GUI_PanelControlador(GUI_Panel& panel);
};

#endif /*__GUI_PANEL_CONTROLADOR_H__*/
