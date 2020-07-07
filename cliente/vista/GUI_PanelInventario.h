#ifndef __GUI_PANEL_INVENTARIO_H__
#define __GUI_PANEL_INVENTARIO_H__

#include <vector>
#include "../vista/GUI_Panel.h"
#include "../vista/Imagen.h"
#include "../modelo/DatosPersonaje.h"

class GUI_PanelInventario : public GUI_Panel{
private:
	Imagen mueca_equipado;
	std::atomic<uint16_t>* equipados;
public:
	GUI_PanelInventario(EntornoGrafico& entorno, Colores& paleta,
	 BancoImagenesEquipo& imagenes_equipo, std::atomic<uint16_t>* inventario,
	 std::atomic<uint16_t>* equipados);
	void actualizarDimension();
	void render() override;
};

#endif /*__GUI_PANEL_INVENTARIO_H__*/
