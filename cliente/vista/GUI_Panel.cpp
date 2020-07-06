#include "GUI_Panel.h"

void GUI_Panel::dibujarCasilla(int i, int j, SDL_Color& fondo){
	renderer -> setColor(fondo);
	renderer -> rectSolido(i, j, LADO_CASILLA, LADO_CASILLA);
	renderer -> setColor(paleta.inv_sombra);
	renderer -> rectSolido(i,j,LADO_CASILLA,2);
}

GUI_Panel::GUI_Panel(EntornoGrafico& entorno, Colores& paleta,
 BancoImagenesEquipo& imagenes_equipo, std::atomic<uint16_t>* inventario,
 SDL_Rect marco) : imagenes_equipo(imagenes_equipo),
  paleta(paleta), inventario(inventario), marco(marco){
	entorno.agregarRendereable(this);
	visible = false;
}

void GUI_Panel::render(){
	if(!visible) return;
	SDL_Color color_fondo;

	renderer -> setColor(paleta.inv_frente);
	renderer -> rectSolido(marco.x, marco.y,
	 SEPARACION + marco.w*(SEPARACION + LADO_CASILLA),
	 SEPARACION + marco.h*(SEPARACION + LADO_CASILLA));

	for(int j = 0; j < marco.h; j++){
		color_fondo = (j % 2) ? paleta.inv_fondo2 : paleta.inv_fondo; 
		for(int i = 0; i < marco.w; i++){
			dibujarCasilla(marco.x + SEPARACION + i*(LADO_CASILLA + SEPARACION),
			 marco.y + SEPARACION + j*(LADO_CASILLA + SEPARACION), color_fondo);
			imagenes_equipo.render(inventario[j*marco.w + i],
			 marco.x + SEPARACION + i*(LADO_CASILLA + SEPARACION),
			 marco.y + SEPARACION + j*(LADO_CASILLA + SEPARACION));
		}
	}

	renderer -> setColor(paleta.inv_luz);
	renderer -> rectSolido(marco.x, marco.y,
	 SEPARACION + marco.w*(SEPARACION + LADO_CASILLA),
	 SEPARACION);
}
