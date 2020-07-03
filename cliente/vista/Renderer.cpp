#include "Renderer.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include "ErrorGrafico.h"
#include "Ventana.h"
#include "Colores.h"

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

void Renderer::limpiarTextura(SDL_Texture* textura) {
    if (!textura) return;
    SDL_Texture* objetivo_actual = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, textura);
    setColor(0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, objetivo_actual);
}

void Renderer::presentar() {
    SDL_RenderPresent(renderer);
    desplazamientoX = 0;
    desplazamientoY = 0;
    escala = 1.0f;
}

SDL_Texture* Renderer::textura(int ancho, int alto){
    SDL_Texture* retorno = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, ancho, alto);
    SDL_Texture* objetivo_actual = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, retorno);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, objetivo_actual);
    SDL_SetTextureBlendMode(retorno, SDL_BLENDMODE_BLEND);
    return retorno;
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

void Renderer::escalar(float factor) {
    this->escala = factor;
}

void Renderer::setColor(std::string hexa) {
    SDL_Color temp = Colores::colorDesdeHexa(hexa);
    this->setColor(temp);
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
    int min_x = std::min(x1, x2);
    int min_y = std::min(y1, y2);
    int ancho = abs(x1 - x2);
    int alto = abs(y1 - y2);
    SDL_Rect rectangulo = {min_x, min_y, ancho, alto};
    rectangulo = transformar(rectangulo);
    SDL_RenderDrawLine(renderer, rectangulo.x, rectangulo.y, rectangulo.x + 
                                    rectangulo.w, rectangulo.y + rectangulo.h);
}

void Renderer::rect(int x, int y, int ancho, int alto) {
    rect_render = transformar(x, y, ancho, alto);
    SDL_RenderDrawRect(renderer, &rect_render);
}

void Renderer::rect(SDL_Rect& rect){
    SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::rectSolido(int x, int y, int ancho, int alto) {
    rect_render = transformar(x, y, ancho, alto);
    SDL_RenderFillRect(renderer, &rect_render);
}

void Renderer::rectSolido(SDL_Rect& rect){
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::renderTexturaTexto(SDL_Surface* superficie, int x, int y) {
    SDL_Rect textura_mascara = {};
    SDL_Rect render_mascara = {};
    SDL_Texture* textura = texturaDesdeSuperficie(superficie);
    SDL_FreeSurface(superficie);
    SDL_QueryTexture(textura, NULL, NULL, &textura_mascara.w,
     &textura_mascara.h);
    render_mascara.x = x;
    render_mascara.y = y;
    render_mascara.w = textura_mascara.w;
    render_mascara.h = textura_mascara.h;
    renderTextura(textura, textura_mascara, render_mascara);
    SDL_DestroyTexture(textura); // TODO: Se podría bufferear
}

void Renderer::texto(const std::string& text) {
    texto(text, 0, 0);
}

void Renderer::texto(const std::string& text, int x, int y) {
    TTF_Font* font = entorno.getFuente(); 
    SDL_Surface* superficie = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!superficie) 
        throw ErrorGrafico("No se pudo cargar generar textura de texto%s\n",
                                                                TTF_GetError());
    renderTexturaTexto(superficie, x, y);
}

void  Renderer::textoATextura(SDL_Texture* textura, const std::string& text,
     int x, int y){
    SDL_Texture* objetivo_actual = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, textura);
    texto(text, x, y);
    SDL_SetRenderTarget(renderer, objetivo_actual);
}

 void Renderer::calcularDimensionTexto(const std::string& text,
  int* ancho, int* alto){
    TTF_SizeText(entorno.getFuente(), text.c_str(), ancho, alto);
 }

SDL_Rect Renderer::transformar(SDL_Rect& rect) {
    return transformar(rect.x, rect.y, rect.w, rect.h);
}

SDL_Rect Renderer::transformar(int x, int y, int ancho, int alto) {
    SDL_Rect transformado = {x, y, ancho, alto};
    transformado.x = transformado.x * escala + desplazamientoX;
    transformado.y = transformado.y * escala + desplazamientoY;
    transformado.w *= escala;
    transformado.h *= escala;
    return transformado;
}

SDL_Point Renderer::transformar(SDL_Point& punto) {
    SDL_Point transformado = punto;
    transformado.x = transformado.x * escala + desplazamientoX;
    transformado.y = transformado.y * escala + desplazamientoY;
    return transformado;
}

void Renderer::renderTextura(SDL_Texture* texture, SDL_Rect& origen_mascara, 
                                                    SDL_Rect& render_mascara) {
    rect_render = transformar(render_mascara);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, texture, &origen_mascara, &this->rect_render);
}
