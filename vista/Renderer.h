#ifndef RENDERER_H
#define RENDERER_H

#include "EntornoGrafico.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <string>

class Ventana;

class Renderer {
public:
    explicit Renderer(EntornoGrafico& entorno);
    ~Renderer();
    void limpiar();
    void presentar();
    void desplazar(int desplazamientoX, int desplazamientoY);

    void rect(int x, int y, int ancho, int alto);
    void rectSolido(int x, int y, int ancho, int alto);
    void linea(int x1, int y1, int x2, int y2);
    
    void setColor(SDL_Color& color);
    void setColor(Uint8 escala);
    void setColor(Uint8 rojo, Uint8 verde, Uint8 azul);
    void setColor(Uint8 rojo, Uint8 verde, Uint8 azul, Uint8 alpha);

    void texto(const std::string& text);
    void texto(const std::string& text, int x, int y);
    void renderTextura(SDL_Texture* texture, SDL_Rect& origen_mascara, 
                                        SDL_Rect& render_mascara); // Maybe x, y
    
    SDL_Texture* texturaDesdeSuperficie(SDL_Surface* surface);
    SDL_Texture* texturaDesdeArchivoImagen(const std::string& path);
    
private:
    SDL_Rect transformar(SDL_Rect& rect);
    SDL_Rect transformar(int x, int y, int ancho, int alto);
    SDL_Point transformar(SDL_Point& punto);
    void renderTexturaTexto(SDL_Surface* superficie, int x, int y);
    SDL_Renderer* renderer;
    EntornoGrafico& entorno;
    
    SDL_Color color = {};

    int desplazamientoX = 0;
    int desplazamientoY = 0;
    SDL_Rect rect_render = {};
};

#endif
