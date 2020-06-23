#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "audio.h"

int main(int argc, char const *argv[])
{
	//Inicializacion

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);

    SDL_Window* ventana = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500,0);
    if (!ventana)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    initAudio();

    //Cargar imagen
     SDL_Surface* superficie = IMG_Load("imagen.png");

    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie);
    SDL_FreeSurface(superficie);
    SDL_RenderCopy(renderer, textura, NULL, NULL);


    //Audio
    playMusic("door1.wav", SDL_MIX_MAXVOLUME);
    playSound("door1.wav", SDL_MIX_MAXVOLUME / 2);

    //Salida
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    endAudio();
    SDL_Quit();
	return 0;
}