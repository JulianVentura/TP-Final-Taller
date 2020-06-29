#include <SDL2/SDL_render.h>

#include "Ventana.h"
#include "../vista/GUI_Dock.h"

GUI_Dock::GUI_Dock(EntornoGrafico& entorno, Colores& paleta) :
fondo(entorno,"assets/fondoDock.png"),
borde(entorno,"assets/bordeDock.png"),
paleta(paleta){
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_Dock::actualizarDimension(){
	int ventana_ancho = ventana -> getAncho();
	int ventana_alto = ventana -> getAlto();
	ancho = ventana_ancho*0.6;
	alto = 50;
	nimg = ancho / 50;
	x = ventana_ancho*0.2;
	y = ventana_alto - alto;

}

void GUI_Dock::render(){
	for(int i = 0; i < nimg;i++){
		fondo.setPosicion(x + i*50,y);
		fondo.render();
	}

	fondo.setMascara(0,0,ancho - nimg*50, 50);
	fondo.setPosicion(x + nimg*50,y);
	fondo.render();
	fondo.setMascara(0,0, 50, 50);

	borde.setPosicion(x - 6,y - 8);
	borde.setMascara(0, 0, 21, 58);
	borde.render();

	borde.setPosicion(x + ancho - 15,y - 8);
	borde.setMascara(21, 0,21,58);
	borde.render();
}