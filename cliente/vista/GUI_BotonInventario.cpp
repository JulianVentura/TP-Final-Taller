#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonInventario.h"
#include "Ventana.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno,
 Colores& paleta, std::atomic<int>* inventario )
  : imagen(entorno,"assets/botonInventario.png"), imagenes_equipo(entorno),
   paleta(paleta),inventario(inventario){
	entorno.agregarRendereable(this);
	visible = false;
	actualizarDimension();
}

void GUI_BotonInventario::dibujarCasilla(int i, int j, SDL_Color& fondo){
	renderer -> setColor(fondo);
	renderer -> rectSolido(i, j, LADO_CASILLA, LADO_CASILLA);
	renderer -> setColor(paleta.inv_sombra);
	renderer -> rectSolido(i,j,LADO_CASILLA,2);
}

void GUI_BotonInventario::actualizarDimension(){
	x = ventana->getAncho()*0.2 + 4;
	y = ventana->getAlto() - 50;
	imagen.setPosicion(x,y - 10);
}

void GUI_BotonInventario::render() {
	imagen.render();
	for(int i = 1;i < 3;i++){
		renderer -> setColor(paleta.barra_fondo);
		renderer -> rectSolido(x + 2*SEPARACION + i*(LADO_CASILLA + SEPARACION),
		 y, LADO_CASILLA, LADO_CASILLA);
		renderer -> setColor(paleta.inv_frente);
		renderer -> rect(x + 2*SEPARACION + i*(LADO_CASILLA + SEPARACION),
		 y, LADO_CASILLA, LADO_CASILLA);
	}
	if(!visible) return;

	int xx = x - 2*SEPARACION - LADO_CASILLA;
	int yy = y - 4*SEPARACION - 6*(SEPARACION + LADO_CASILLA);
	renderer -> setColor(paleta.inv_frente);
	renderer -> rectSolido(xx, yy, SEPARACION + 3*(SEPARACION + LADO_CASILLA),
	 SEPARACION + 6*(SEPARACION + LADO_CASILLA));

	SDL_Color fondo;
	for(int j = 0; j < INV_ALTO;j++){
		fondo = (j % 2) ? paleta.inv_fondo2 : paleta.inv_fondo; 
		for(int i = 0;i < INV_ANCHO;i++){
			dibujarCasilla(xx + SEPARACION + i*(LADO_CASILLA + SEPARACION),
			 yy + SEPARACION + j*(LADO_CASILLA + SEPARACION), fondo);
			imagenes_equipo.render(inventario[j*INV_ANCHO + i], xx +
			 SEPARACION + i*(LADO_CASILLA + SEPARACION), yy + SEPARACION +
			   j*(LADO_CASILLA + SEPARACION));
		}
	}

	renderer -> setColor(paleta.inv_luz);
	renderer -> rectSolido(xx, yy, SEPARACION + 3*(SEPARACION + LADO_CASILLA),
	 SEPARACION);
}
