#ifndef __GUI_PANEL_TIENDA_H__
#define __GUI_PANEL_TIENDA_H__

#include "../vista/GUI_Panel.h"
#include "../vista/GUI_OroAlmacenado.h"

class GUI_PanelTienda : public GUI_Panel{
private:
	GUI_OroAlmacenado oro_almacenado;
	std::atomic<uint16_t>* precios;
	void dibujarPrecio(int precio, int i, int j);
public:
	std::atomic<bool>& activo;
	GUI_PanelTienda(EntornoGrafico& entorno, Colores& paleta,
	 BancoImagenesEquipo& imagenes_equipo, std::atomic<uint16_t>* inventario,
	 std::atomic<uint16_t>* precios, std::atomic<uint32_t>& oro_almacenado,
	 std::atomic<bool>& activo);
	void render() override;
	void actualizarDimension();
};

#endif /*__GUI_PANEL_TIENDA_H__*/
