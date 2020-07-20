#include "GUI_Clickeable.h"

GUI_Clickeable::GUI_Clickeable(SDL_Rect rect)
: rect (rect){}

bool GUI_Clickeable::operator()(SDL_Event& evento){
	SDL_Point punto = {evento.button.x, evento.button.y};
	if(!SDL_PointInRect(&punto, &rect)) return false;
	return enClick();
}



