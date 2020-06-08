#include "Renderer.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>
#include <string>
#include "ErrorGrafico.h"
#include "Ventana.h"

#define MAX_COLOR_VALUE 0xFF
#define RENDER_INDEX -1
#define RENDER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

Renderer::Renderer(EntornoGrafico& entorno) : entorno(entorno) {
    renderer = SDL_CreateRenderer(entorno.ventana->ventana, RENDER_INDEX,
        RENDER_FLAGS);
    if (!renderer) 
        throw ErrorGrafico("No se pudo iniciar renderer %s\n", SDL_GetError());
    entorno.ventana->renderer = this;
    entorno.renderer = this;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}
void Renderer::translate(int xoff, int yoff) {
    this->xoff = xoff;    
    this->yoff = yoff;    
}

void Renderer::setColor(SDL_Color& color) {
    setColor(color.r, color.g, color.b, color.a);
}

void Renderer::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    setColor(red, green, blue, MAX_COLOR_VALUE);
}

void Renderer::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    color = {red, green, blue, alpha};
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::line(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::rect(SDL_Rect& rect) {
    SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::fillRect(SDL_Rect& rect) {
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Texture* Renderer::texturaDesdeSuperficie(SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) 
        throw ErrorGrafico("No se pudo crear textura %s\n", SDL_GetError());
    return texture;
}

SDL_Texture* Renderer::loadImage(const std::string& path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) 
        throw ErrorGrafico("No se pudo cargar el archivo %s: Error %s\n", 
                                                path.c_str(), IMG_GetError());
    return texture;
}

void Renderer::text(const std::string& text) {
    TTF_Font* font = entorno.getFont(); 
    SDL_Surface* superficie = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!superficie) 
        throw ErrorGrafico("No se pudo cargar generar textura de texto%s\n",
                                                                TTF_GetError());
    SDL_Rect render_clip = {};
    SDL_Texture* textura = texturaDesdeSuperficie(superficie);
    SDL_FreeSurface(superficie);
    SDL_QueryTexture(textura, NULL, NULL, &render_clip.w, &render_clip.h);
    renderTextura(textura, render_clip, render_clip);
    SDL_DestroyTexture(textura); // Se podría bufferear
}

void Renderer::renderTextura(SDL_Texture* texture, SDL_Rect& src_clip, 
                                                        SDL_Rect& render_clip) {
    SDL_Rect _render_clip = render_clip;
    _render_clip.x -= xoff;
    _render_clip.y -= yoff;
    SDL_RenderCopy(renderer, texture, &src_clip, &_render_clip);
}
