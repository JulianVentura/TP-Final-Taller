#include "GUI_Panel_Controlador.h"

GUI_PanelControlador::GUI_PanelControlador(GUI_Panel& panel) :
GUI_BotonControlador(panel.marco.x, panel.marco.y,
	 SEPARACION + panel.marco.w*(SEPARACION + LADO_CASILLA),
	 SEPARACION + panel.marco.h*(SEPARACION + LADO_CASILLA)), panel(panel){}

bool GUI_PanelControlador::enClick(){
	return panel.visible;
}

int GUI_PanelControlador::obtenerIndiceClick(){
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return (mouse_x - panel.marco.x)/(LADO_CASILLA + SEPARACION) +
			panel.marco.w*((mouse_y - panel.marco.y)/
				(LADO_CASILLA + SEPARACION));
}
