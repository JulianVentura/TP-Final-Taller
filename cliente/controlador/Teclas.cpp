#include "Teclas.h"

Teclas::Teclas(ServidorProxy& servidor) : servidor(servidor){}

void Teclas::manejarEvento(SDL_Event& evento){
	if (evento.type == SDL_KEYDOWN) {
		switch(evento.key.keysym.sym){
			case TECLA_ARRIBA:
			//servidor.moverArriba()
			return;

			case TECLA_ABAJO:
			return;

			case TECLA_IZQUIERDA:
			return;

			case TECLA_DERECHA:
			return;

			default:
			return;
		}
    }
    //servidor.detenerMovimiento()
}