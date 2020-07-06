#include "GUI_PanelInventario.h"

GUI_PanelInventario::GUI_PanelInventario(EntornoGrafico& entorno,
 Colores& paleta, BancoImagenesEquipo& imagenes_equipo,
  std::atomic<uint16_t>* inventario)
: GUI_Panel(entorno, paleta, imagenes_equipo, inventario, {}){
	marco.w = 3;
	marco.h = 6;
	actualizarDimension();
}


void GUI_PanelInventario::actualizarDimension(){
	marco.x = ventana->getAncho()*0.2 - (marco.w/2)*(SEPARACION + LADO_CASILLA);
	marco.y = ventana->getAlto()*0.9 - marco.h*(SEPARACION + LADO_CASILLA)
	 - 4*SEPARACION;
}
