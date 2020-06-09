#include <SDL.h>
#include <SDL_image.h>

#include "dibujable.h"

SDL_Texture* cargar_textura(const char* camino_textura, SDL_Renderer* renderer){

    SDL_Surface* superficie = IMG_Load(camino_textura);
    
    if (!superficie) return NULL;

    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie);
    SDL_FreeSurface(superficie);

    return textura;
}

Dibujable::Dibujable(int x,int y,int ancho,int largo,const char* camino_textura,SDL_Renderer* renderer){
    marco.x = x;
    marco.y = y;
    marco.w = ancho;
    marco.h = largo;
    textura = cargar_textura(camino_textura,renderer);
}

void Dibujable::dibujar(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, textura, NULL, &marco);
}

Dibujable::~Dibujable(){
    SDL_DestroyTexture(textura);
}