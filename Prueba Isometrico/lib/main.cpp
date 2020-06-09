#include <stdio.h>
#include <list>
#include <iterator> 
#include <SDL.h>
#include <SDL_image.h>

#include <math.h>

#include "vector2D.h"
#include "ente.h"
#include "mapa.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace std;

int main( int argc, char* args[] )
{

    // INICIALIZACION GENERAL //

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);

    SDL_Window* ventana = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);
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

    // INICIALIZACION DE OBJETOS Y VARIABLES
    SDL_Event event;
    bool close_requested = false;

    int up = 0;
    int left = 0;
    int right = 0;
    int down = 0;
    vector2D control(0,0);
    Mapa mapa(renderer);
    list <Ente*> lista_entes;
    Ente jugador(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,16,16,"luna.png",renderer);
    lista_entes.push_back(&jugador);

    // CICLO PRINCIPAL //

        SDL_RenderClear(renderer);
        mapa.dibujar(renderer);
        
    while (!close_requested)
    {
        // PROCESAMIENTO DE EVENTOS //

        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    close_requested = 1;
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        up = 0;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left = 0;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        down = 0;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right = 0;
                        break;
                    }
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        up = 1;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left = 1;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        down = 1;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right = 1;
                        break;
                    }
                    break;
            }
        }

        control.x = right - left;
        control.y = down - up;
        jugador.mover(control);

        // RENDERIZADO //
        

    
        

        
/*
        for(Ente* ente : lista_entes){
           ente -> dibujar(renderer);
           ente -> tic();
        }
*/
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1000/60);
    }

    // FIN //
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

	return 0;
}