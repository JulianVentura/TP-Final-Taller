#ifndef __TECLAS_H__
#define __TECLAS_H__

#include <SDL2/SDL_events.h>

#include "../modelo/ServidorProxy.h"

#define TECLA_ARRIBA    SDLK_w
#define TECLA_DERECHA   SDLK_d
#define TECLA_ABAJO     SDLK_s
#define TECLA_IZQUIERDA SDLK_a

class Teclas{
private:
	ServidorProxy& servidor;
public:
	explicit Teclas(ServidorProxy& servidor);
	void manejarEvento(SDL_Event& evento);
};

#endif /* __TECLAS_H__*/