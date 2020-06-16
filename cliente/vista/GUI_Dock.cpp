#include <SDL2/SDL_render.h>

#include "Ventana.h"
#include "../vista/GUI_Dock.h"

GUI_Dock::GUI_Dock(EntornoGrafico& entorno, Colores& paleta) : paleta(paleta){
	entorno.agregarRendereable(this);
	actualizar_dimensiones();
}

void GUI_Dock::actualizar_dimensiones(){
	int ventana_ancho = ventana -> getAncho();
	int ventana_alto = ventana -> getAlto();

	x = ventana_ancho*0.2;
	y = ventana_alto*0.9;
	ancho = ventana_ancho*0.6;
	alto = ventana_alto*0.1;
}

void GUI_Dock::render(){
	renderer -> setColor(paleta.inv_frente);
	renderer -> rectSolido(x, y, ancho, alto);
	renderer -> setColor(paleta.inv_luz);
	renderer -> rectSolido(x, y, ancho, alto/3);
}