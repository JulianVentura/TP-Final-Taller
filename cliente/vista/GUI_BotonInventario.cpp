#include <SDL2/SDL_render.h>

#include "Imagen.h"
#include "IRendereable.h"
#include "GUI_BotonInventario.h"

GUI_BotonInventario::GUI_BotonInventario(EntornoGrafico& entorno, int x, int y)
: imagen(entorno,"assets/botonInventario.png"), x(x), y(y) {
	imagen.setPosicion(x,y);
	ancho = 3; alto = 6; //HARDCODEO
	visible = false;
	frente.r = 80;frente.g = 57; frente.b = 37;frente.a = 255;
	fondo.r = 46;fondo.g = 31; fondo.b = 21;fondo.a = 255;
	sombra.r = 33;sombra.g = 22; sombra.b = 14; sombra.a = 255;
	luz.r = 94;luz.g = 75; luz.b = 51;luz.a = 255;
}

void GUI_BotonInventario::render() {
	imagen.render();
	if(!visible) return;

	renderer -> setColor(frente);
	renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON,
	 y - 2*SEPARACION - 6*(SEPARACION + LADO_BOTON),SEPARACION +
	3*(SEPARACION + LADO_BOTON), SEPARACION + 6*(SEPARACION + LADO_BOTON));

	for(int i = 0;i < ancho;i++){
		for(int j = 0; j < alto;j++){
			renderer -> setColor(fondo);
			renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON
				+ SEPARACION + i*(LADO_BOTON + SEPARACION),
				y - SEPARACION - 6*(SEPARACION + LADO_BOTON) +
				j*(LADO_BOTON + SEPARACION), LADO_BOTON, LADO_BOTON);
			renderer -> setColor(luz);
			renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON
				+ SEPARACION + i*(LADO_BOTON + SEPARACION),
				y - SEPARACION - 6*(SEPARACION + LADO_BOTON) +
				j*(LADO_BOTON + SEPARACION) - 2,LADO_BOTON,2);
			renderer -> setColor(sombra);
			renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON
				+ SEPARACION + i*(LADO_BOTON + SEPARACION),
				y - SEPARACION - 6*(SEPARACION + LADO_BOTON) +
				j*(LADO_BOTON + SEPARACION) + 1,LADO_BOTON,2);
		}
	}

	renderer -> setColor(luz);
	renderer -> rectSolido(x - 2*SEPARACION - LADO_BOTON,
	 y - 2*SEPARACION - 6*(SEPARACION + LADO_BOTON), LADO_BOTON, SEPARACION);

}
