#include <SDL2/SDL_render.h>
#include "GUI_Barra.h"

int capacidad_actual,capacidad_max;
GUI_Barra::GUI_Barra(EntornoGrafico& entorno, Colores& paleta,
 SDL_Color& principal, SDL_Color& secundario, int& capacidad_max,
  int& capacidad_actual) :
   paleta(paleta),
   principal(principal),
   secundario(secundario),
   capacidad_max(capacidad_max),
   capacidad_actual(capacidad_actual){
		entorno.agregarRendereable(this);
}
	
void GUI_Barra::render(){
	renderer -> setColor(paleta.barra_fondo);
	renderer -> rectSolido(marco);

	renderer -> setColor(secundario);
	renderer -> rectSolido(marco.x, marco.y, (marco.w*capacidad_actual)/
		capacidad_max, marco.h);

	renderer -> setColor(principal);
	renderer -> rectSolido(marco.x, marco.y + marco.h/3,
	(marco.w*capacidad_actual)/capacidad_max, marco.h/3);

	renderer -> setColor(paleta.inv_frente);
	renderer -> rect(marco.x - 1,marco.y - 1, marco.w + 1,marco.h + 1);

	renderer -> setColor(paleta.inv_fondo);
	renderer -> rect(marco.x - 1,marco.y + marco.h, marco.w + 1, 1);
}

GUI_Barra::~GUI_Barra(){}
