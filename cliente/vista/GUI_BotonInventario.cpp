#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonInventario.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno,
 Colores& paleta, int x, int y)
: imagen(entorno,"assets/botonInventario.png"), paleta(paleta), x(x), y(y) {
	entorno.agregarRendereable(this);
	imagen.setPosicion(x,y);
	ancho = 3; alto = 6; //HARDCODEO
	visible = false;
}

void GUI_BotonInventario::render() {
	imagen.render();
	if(!visible) return;
	renderer -> setColor(paleta.inv_frente);
	renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON,
	 y - 2*SEPARACION - 6*(SEPARACION + LADO_BOTON),SEPARACION +
	3*(SEPARACION + LADO_BOTON), SEPARACION + 6*(SEPARACION + LADO_BOTON));

	for(int i = 0;i < ancho;i++){
		for(int j = 0; j < alto;j++){
			renderer -> setColor(paleta.inv_fondo);
			renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON
				+ SEPARACION + i*(LADO_BOTON + SEPARACION),
				y - SEPARACION - 6*(SEPARACION + LADO_BOTON) +
				j*(LADO_BOTON + SEPARACION), LADO_BOTON, LADO_BOTON);
			renderer -> setColor(paleta.inv_luz);
			renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON
				+ SEPARACION + i*(LADO_BOTON + SEPARACION),
				y - SEPARACION - 6*(SEPARACION + LADO_BOTON) +
				j*(LADO_BOTON + SEPARACION) - 2,LADO_BOTON,2);
			renderer -> setColor(paleta.inv_sombra);
			renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON
				+ SEPARACION + i*(LADO_BOTON + SEPARACION),
				y - SEPARACION - 6*(SEPARACION + LADO_BOTON) +
				j*(LADO_BOTON + SEPARACION) + 1,LADO_BOTON,2);
		}
	}

	renderer -> setColor(paleta.inv_luz);
	renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON,
	 y - 2*SEPARACION - 6*(SEPARACION + LADO_BOTON), SEPARACION +
	3*(SEPARACION + LADO_BOTON), SEPARACION);

}
