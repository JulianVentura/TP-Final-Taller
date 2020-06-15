#include <SDL2/SDL_render.h>
#include "GUI_Barra.h"

#include <iostream>

int capacidad_actual,capacidad_max;
Barra::Barra(EntornoGrafico& entorno, SDL_Rect& marco, SDL_Color& color ,
	int capacidad_max, int capacidad_actual) : marco(marco), principal(color),
	 capacidad_max(capacidad_max) , capacidad_actual(capacidad_actual){
		entorno.agregarRendereable(this);
		secundario.r = principal.r*2;  
		secundario.g = principal.g*2;
		secundario.b = principal.b*2;
		secundario.a = principal.a;
}
	
void Barra::render(){
	int w = marco.w;
	renderer -> setColor(principal);
	renderer -> rectSolido(marco);
	marco.w *= (float)capacidad_actual/(float)capacidad_max; 
	renderer -> setColor(secundario);
	renderer -> rectSolido(marco);
	marco.w = w;
}
