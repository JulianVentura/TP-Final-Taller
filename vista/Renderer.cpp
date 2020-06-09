#include "Renderer.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
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

void Renderer::desplazar(int xoff, int yoff) {
    this->xoff += xoff;    
    this->yoff += yoff;    
}

void Renderer::setColor(Uint8 escala) {
    setColor(escala, escala, escala);
}

void Renderer::setColor(Uint8 rojo, Uint8 verde, Uint8 azul) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    setColor(rojo, verde, azul, MAX_COLOR_VALUE);
}

void Renderer::setColor(Uint8 rojo, Uint8 verde, Uint8 azul, Uint8 alpha) {
    color = { rojo, verde, azul, alpha };
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, rojo, verde, azul, alpha);
}

void Renderer::setColor(SDL_Color& color) {
    setColor(color.r, color.g, color.b, color.a);
}

void Renderer::limpiar() {
    SDL_RenderClear(renderer);
}

void Renderer::presentar() {
    SDL_RenderPresent(renderer);
}

void Renderer::linea(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::rect(int x, int y, int ancho, int alto) {
    rect_render = { x, y, ancho, alto };
    transformar(rect_render);
    SDL_RenderDrawRect(renderer, &rect_render);
}

void Renderer::rectSolido(int x, int y, int ancho, int alto) {
    rect_render = { x, y, ancho, alto };
    transformar(rect_render);
    SDL_RenderFillRect(renderer, &rect_render);
}

SDL_Texture* Renderer::texturaDesdeSuperficie(SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) 
        throw ErrorGrafico("No se pudo crear textura %s\n", SDL_GetError());
    return texture;
}

SDL_Texture* Renderer::texturaDesdeArchivoImagen(const std::string& path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) 
        throw ErrorGrafico("No se pudo cargar el archivo %s: Error %s\n", 
                                                path.c_str(), IMG_GetError());
    return texture;
}

void Renderer::texto(const std::string& text) {
    texto(text, 0, 0);
}

void Renderer::renderTexturaTexto(SDL_Surface* superficie, int x, int y) {
    SDL_Rect render_clip = {};
    SDL_Texture* textura = texturaDesdeSuperficie(superficie);
    SDL_FreeSurface(superficie);
    SDL_QueryTexture(textura, NULL, NULL, &render_clip.w, &render_clip.h);
    render_clip.x = x;
    render_clip.y = y;
    renderTextura(textura, render_clip, render_clip);
    SDL_DestroyTexture(textura); // Se podría bufferear
}

void Renderer::texto(const std::string& text, int x, int y) {
    TTF_Font* font = entorno.getFuente(); 
    SDL_Surface* superficie = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!superficie) 
        throw ErrorGrafico("No se pudo cargar generar textura de texto%s\n",
                                                                TTF_GetError());
    renderTexturaTexto(superficie, x, y);
}

void Renderer::transformar(SDL_Rect& clip) {
    rect_render = clip;
    rect_render.x -= xoff;
    rect_render.y -= yoff;
}

void Renderer::renderTextura(SDL_Texture* texture, SDL_Rect& src_clip, 
                                                        SDL_Rect& render_clip) {
    transformar(render_clip);
    SDL_RenderCopy(renderer, texture, &src_clip, &this->rect_render);
}
