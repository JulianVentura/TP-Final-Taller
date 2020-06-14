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

void Renderer::limpiar() {
    SDL_RenderClear(renderer);
}

void Renderer::presentar() {
    SDL_RenderPresent(renderer);
    // Se podría reiniciar el desplazamientoX, desplazamientoY
}

SDL_Texture* Renderer::texturaDesdeSuperficie(SDL_Surface* superficie) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, superficie);
    if (!texture) 
        throw ErrorGrafico("No se pudo crear textura %s\n", SDL_GetError());
    return texture;
}

SDL_Texture* Renderer::texturaDesdeArchivoImagen(const std::string& ruta) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, ruta.c_str());
    if (!texture) 
        throw ErrorGrafico("No se pudo cargar el archivo %s: Error %s\n", 
                                                ruta.c_str(), IMG_GetError());
    return texture;
}

void Renderer::desplazar(int desplazamientoX, int desplazamientoY) {
    this->desplazamientoX += desplazamientoX;    
    this->desplazamientoY += desplazamientoY;    
}

void Renderer::setColor(SDL_Color& color) {
    setColor(color.r, color.g, color.b, color.a);
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


void Renderer::linea(int x1, int y1, int x2, int y2) {
    SDL_Point comienzo = { x1, y1 };
    SDL_Point fin = { x2, y2 };
    comienzo = transformar(comienzo);
    fin = transformar(fin);
    SDL_RenderDrawLine(renderer, comienzo.x, comienzo.y, fin.x, fin.y);
}

void Renderer::rect(int x, int y, int ancho, int alto) {
    rect_render = transformar(x, y, ancho, alto);
    SDL_RenderDrawRect(renderer, &rect_render);
}

void Renderer::rectSolido(int x, int y, int ancho, int alto) {
    rect_render = transformar(x, y, ancho, alto);
    SDL_RenderFillRect(renderer, &rect_render);
}

void Renderer::rectSolido(SDL_Rect& rect){
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::renderTexturaTexto(SDL_Surface* superficie, int x, int y) {
    SDL_Rect render_mascara = {};
    SDL_Texture* textura = texturaDesdeSuperficie(superficie);
    SDL_FreeSurface(superficie);
    SDL_QueryTexture(textura, NULL, NULL, &render_mascara.w, &render_mascara.h);
    render_mascara.x = x;
    render_mascara.y = y;
    renderTextura(textura, render_mascara, render_mascara);
    SDL_DestroyTexture(textura); // Se podría bufferear
}

void Renderer::texto(const std::string& text) {
    texto(text, 0, 0);
}

void Renderer::texto(const std::string& text, int x, int y) {
    TTF_Font* font = entorno.getFuente(); 
    SDL_Surface* superficie = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!superficie) 
        throw ErrorGrafico("No se pudo cargar generar textura de texto%s\n",
                                                                TTF_GetError());
    renderTexturaTexto(superficie, x, y);
}

SDL_Rect Renderer::transformar(SDL_Rect& rect) {
    return transformar(rect.x, rect.y, rect.w, rect.h);
}

SDL_Rect Renderer::transformar(int x, int y, int ancho, int alto) {
    SDL_Rect transformado = {x, y, ancho, alto};
    transformado.x += desplazamientoX;
    transformado.y += desplazamientoY;
    return transformado;
}

SDL_Point Renderer::transformar(SDL_Point& punto) {
    SDL_Point transformado = punto;
    transformado.x += desplazamientoX;
    transformado.y += desplazamientoY;
    return transformado;
}

void Renderer::renderTextura(SDL_Texture* texture, SDL_Rect& origen_mascara, 
                                                    SDL_Rect& render_mascara) {
    rect_render = transformar(render_mascara);
    SDL_RenderCopy(renderer, texture, &origen_mascara, &this->rect_render);
}
