#include "BuclePrincipal.h"

void BuclePrincipal::correr() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
        	switch(event.type){
        		case SDL_QUIT:
        		quit = true;
        		break;

        		case SDL_MOUSEBUTTONDOWN:
        			for(auto boton : botones){
        				if((*boton)(event)) break;
        			}
        		break;

        		default:
        		ventana->manejarEvento(event);
        	}   
        }
        ventana->render();
    }
}
