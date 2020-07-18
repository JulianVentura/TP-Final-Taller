#include "GUI_PanelTienda.h"

GUI_PanelTienda::GUI_PanelTienda(EntornoGrafico& entorno, Colores& paleta,
	 BancoImagenesEquipo& imagenes_equipo, std::atomic<uint16_t>* inventario,
	 std::atomic<uint16_t>* precios, std::atomic<uint16_t>& oro_almacenado,
	 std::atomic<bool>& activo)
	  : GUI_Panel(entorno, paleta, imagenes_equipo, inventario, {}),
	   oro_almacenado(entorno, paleta, oro_almacenado), precios(precios),
	   activo(activo){
	visible = true;
	marco.w = 3;
	marco.h = 6;
	actualizarDimension();
}

void GUI_PanelTienda::dibujarPrecio(int precio, int i, int j){
	if(precio == 0) return;

	renderer -> setColor(paleta.barra_fondo);
	renderer -> rectSolido(i + LADO_CASILLA/4, j + LADO_CASILLA - 6,
		LADO_CASILLA/2, 15);
	renderer -> setColor(paleta.inv_frente);
	renderer -> rect(i + LADO_CASILLA/4, j + LADO_CASILLA - 6,
		LADO_CASILLA/2, 15);
	renderer -> setColor(paleta.chat_texto);

	int corrimiento_x;
	renderer -> calcularDimensionTexto(std::to_string(precio),
	 &corrimiento_x, NULL);
	renderer -> texto(std::to_string(precio),
	 i + LADO_CASILLA*3/4 - corrimiento_x, j + LADO_CASILLA - 6);
}

void GUI_PanelTienda::render(){
	if(!activo) return;
	GUI_Panel::render();

	for(int j = 0; j < marco.h; j++){
		for(int i = 0; i < marco.w; i++){
			dibujarPrecio(precios[j*marco.w + i],
			 marco.x + SEPARACION + i*(LADO_CASILLA + SEPARACION),
			 marco.y + SEPARACION + j*(LADO_CASILLA + SEPARACION));
		}
	}
	oro_almacenado.render();
}

void GUI_PanelTienda::actualizarDimension(){
	marco.x = ventana->getAncho()*0.8 - (marco.w)*(SEPARACION + LADO_CASILLA)
	 + (marco.w/2)*(SEPARACION + LADO_CASILLA);
	marco.y = ventana->getAlto()*0.9 - marco.h*(SEPARACION + LADO_CASILLA)
	 - 4*SEPARACION;
	oro_almacenado.actualizarDimension();
}
