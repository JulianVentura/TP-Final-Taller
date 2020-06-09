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
    void desplazar(int xoff, int yoff);

    void rect(int x, int y, int ancho, int alto);
    void rectSolido(int x, int y, int ancho, int alto);
    void linea(int x1, int y1, int x2, int y2);
    
    void setColor(SDL_Color& color);
    void setColor(Uint8 escala);
    void setColor(Uint8 rojo, Uint8 verde, Uint8 azul);
    void setColor(Uint8 rojo, Uint8 verde, Uint8 azul, Uint8 alpha);

    void texto(const std::string& text);
    void texto(const std::string& text, int x, int y);
    void renderTextura(SDL_Texture* texture, SDL_Rect& src_clip, 
                                        SDL_Rect& render_clip); // Maybe x, y
    
    SDL_Texture* texturaDesdeSuperficie(SDL_Surface* surface);
    SDL_Texture* texturaDesdeArchivoImagen(const std::string& path);
    
private:
    void transformar(SDL_Rect& clip);
    void renderTexturaTexto(SDL_Surface* superficie, int x, int y);
    SDL_Renderer* renderer;
    EntornoGrafico& entorno;
    
    SDL_Color color = {};

    int xoff = 0;
    int yoff = 0;
    SDL_Rect rect_render = {};
};

#endif
