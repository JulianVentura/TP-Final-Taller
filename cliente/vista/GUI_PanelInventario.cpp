#include "GUI_PanelInventario.h"

#define INV_ALTO  6
#define INV_ANCHO 3
#define ESPACIOS_EQUIPO 4

GUI_PanelInventario::GUI_PanelInventario(EntornoGrafico& entorno,
 Colores& paleta, BancoImagenesEquipo& imagenes_equipo,
  std::atomic<uint16_t>* inventario, std::atomic<uint16_t>* equipados)
: GUI_Panel(entorno, paleta, imagenes_equipo, inventario, {}),
mueca_equipado(entorno, "assets/gui/mueca.png"), equipados(equipados){
	marco.w = INV_ANCHO;
	marco.h = INV_ALTO;
	actualizarDimension();
}


void GUI_PanelInventario::actualizarDimension(){
	marco.x = ventana->getAncho()*0.2 - (marco.w/2)*(SEPARACION + LADO_CASILLA);
	marco.y = ventana->getAlto() - marco.h*(SEPARACION + LADO_CASILLA)
	 - 4*SEPARACION - 50;
}

void GUI_PanelInventario::render(){
	GUI_Panel::render();
	if(!visible) return;
	int i,j,pos;

	for(int k = 0; k < ESPACIOS_EQUIPO;k++){
		pos = equipados[k]; //Copia escencial, evita dibujos fuera de lugar.
		if(pos == -1) continue;
		j = pos/marco.w;
		i = pos - j*marco.w;
		mueca_equipado.setPosicion(marco.x + SEPARACION+ i*(LADO_CASILLA +
		 SEPARACION) + LADO_CASILLA - mueca_equipado.getAncho()/2 - 10,
		marco.y + SEPARACION + j*(LADO_CASILLA + SEPARACION) + LADO_CASILLA
		-mueca_equipado.getAlto()/2 - 10);
		mueca_equipado.render();
	}
}