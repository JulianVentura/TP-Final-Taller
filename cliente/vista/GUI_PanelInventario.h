#ifndef __GUI_PANEL_INVENTARIO_H__
#define __GUI_PANEL_INVENTARIO_H__

#include "../vista/GUI_Panel.h"

class GUI_PanelInventario : public GUI_Panel{
public:
	GUI_PanelInventario(EntornoGrafico& entorno, Colores& paleta,
	 BancoImagenesEquipo& imagenes_equipo, std::atomic<uint16_t>* inventario);
	void actualizarDimension();
};

#endif /*__GUI_PANEL_INVENTARIO_H__*/
