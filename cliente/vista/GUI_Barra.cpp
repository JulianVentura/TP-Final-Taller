#include <SDL2/SDL_render.h>
#include "GUI_Barra.h"

int capacidad_actual,capacidad_max;
GUI_Barra::GUI_Barra(EntornoGrafico& entorno, Colores& paleta, 
	SDL_Color& principal, SDL_Color& secundario, 
	std::atomic<uint16_t>& capacidad_max, std::atomic<uint16_t>& capacidad_actual) :
   paleta(paleta),
   principal(principal),
   secundario(secundario),
   capacidad_max(capacidad_max),
   capacidad_actual(capacidad_actual){
		entorno.agregarRendereable(this);
}
	
void GUI_Barra::render(){
	if(capacidad_max == 0) return;
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

	renderer -> setColor(paleta.chat_texto);

	renderer -> texto(std::to_string(capacidad_actual) + "|" +
	 std::to_string(capacidad_max), marco.x + marco.w/2 - 30, marco.y + marco.h/2 - 12);
}

GUI_Barra::~GUI_Barra(){}
