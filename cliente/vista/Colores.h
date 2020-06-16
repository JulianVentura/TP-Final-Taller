#ifndef __COLORES_H__
#define __COLORES_H__

#include <SDL2/SDL_render.h>

class Colores{
public:
	Colores();
	SDL_Color vida;
	SDL_Color mana;
	SDL_Color exp;
	SDL_Color inv_frente;
	SDL_Color inv_fondo;
	SDL_Color inv_sombra;
	SDL_Color inv_luz;
};

#endif /*__COLORES_H__*/