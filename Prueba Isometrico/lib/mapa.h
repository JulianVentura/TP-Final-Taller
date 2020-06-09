#include <SDL.h>
#include <SDL_image.h>

#define LADO_CELDA 64
#define CANT_TEXT 3

class Mapa{
	int ancho,largo,alto;
	int mapa[10][10][5];
	int altura_text[CANT_TEXT];
	SDL_Texture* texturas[CANT_TEXT];
public:
	Mapa(SDL_Renderer* renderer);
	void dibujar(SDL_Renderer* renderer);
};