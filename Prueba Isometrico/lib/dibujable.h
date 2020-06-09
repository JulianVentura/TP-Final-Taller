#ifndef DIBUJABLE_H
#define DIBUJABLE_H

#include <SDL.h>
#include <SDL_image.h>

class Dibujable{

	protected:
	        SDL_Rect marco;
	        SDL_Texture* textura;

	public:

	    	Dibujable(int x,int y,int ancho,int largo,const char* camino_textura,SDL_Renderer* renderer);

	    	void dibujar(SDL_Renderer* renderer);

	   		~Dibujable();
};

#endif /*DIBUJABLE_H */