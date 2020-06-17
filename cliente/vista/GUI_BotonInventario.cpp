#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonInventario.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno,
 Colores& paleta, int x, int y)
: imagen(entorno,"assets/botonInventario.png"), paleta(paleta), x(x), y(y) {
	entorno.agregarRendereable(this);
	imagen.setPosicion(x,y - 10);
	ancho = 3; alto = 6; //HARDCODEO
	visible = false;
}

void GUI_BotonInventario::dibujarCasilla(int i, int j, SDL_Color& fondo){
	renderer -> setColor(fondo);
	renderer -> rectSolido(i, j, LADO_BOTON, LADO_BOTON);
	renderer -> setColor(paleta.inv_sombra);
	renderer -> rectSolido(i,j,LADO_BOTON,2);
}

void GUI_BotonInventario::render() {
	imagen.render();

	for(int i = 1;i < 3;i++){
		renderer -> setColor(paleta.barra_fondo);
		renderer -> rectSolido(x + i*(LADO_BOTON + SEPARACION),
		 y, LADO_BOTON, LADO_BOTON);
		renderer -> setColor(paleta.inv_frente);
				renderer -> rect(x + i*(LADO_BOTON + SEPARACION),
		 y, LADO_BOTON, LADO_BOTON);
	}

	if(!visible) return;
	renderer -> setColor(paleta.inv_frente);
	renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON,
	 y - 2*SEPARACION - 6*(SEPARACION + LADO_BOTON),SEPARACION +
	3*(SEPARACION + LADO_BOTON), SEPARACION + 6*(SEPARACION + LADO_BOTON));

	SDL_Color fondo;
	for(int j = 0; j < alto;j++){
		fondo = (j % 2) ? paleta.inv_fondo2 : paleta.inv_fondo; 
		for(int i = 0;i < ancho;i++){
			dibujarCasilla(x - 2*SEPARACION - LADO_BOTON + SEPARACION +
			 i*(LADO_BOTON + SEPARACION), y - SEPARACION - 6*(SEPARACION
			  + LADO_BOTON) + j*(LADO_BOTON + SEPARACION), fondo);
		}
	}

	renderer -> setColor(paleta.inv_luz);
	renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON,
	 y - 2*SEPARACION - 6*(SEPARACION + LADO_BOTON), SEPARACION +
	3*(SEPARACION + LADO_BOTON), SEPARACION);
}
