#include <SDL2/SDL_render.h>
#include "GUI_Barra.h"

int capacidad_actual,capacidad_max;
GUI_Barra::GUI_Barra(EntornoGrafico& entorno, SDL_Color& color,
 int& capacidad_max, int& capacidad_actual) : principal(color),
  capacidad_max(capacidad_max), capacidad_actual(capacidad_actual){
		entorno.agregarRendereable(this);
		secundario.r = principal.r*2;  
		secundario.g = principal.g*2;
		secundario.b = principal.b*2;
		secundario.a = principal.a;
}
	
void GUI_Barra::render(){
	int w = marco.w;
	int h = marco.h;
	int y2 = marco.y;
	renderer -> setColor(24,24,24,255);
	renderer -> rectSolido(marco);

	marco.w = (float)(marco.w*capacidad_actual)/(float)capacidad_max; 
	renderer -> setColor(principal);
	renderer -> rectSolido(marco);

	marco.y += marco.h/3; marco.h /= 3;
	renderer -> setColor(secundario);
	renderer -> rectSolido(marco);
	marco.w = w;
	marco.h = h;
	marco.y = y2;
}

GUI_Barra::~GUI_Barra(){}
