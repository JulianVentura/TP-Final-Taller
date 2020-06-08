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
    void clear();
    void present();
    void translate(int xoff, int yoff);
    void rect(SDL_Rect& rect);
    void fillRect(SDL_Rect& rect);
    void line(int x1, int y1, int x2, int y2);
    
    void setColor(SDL_Color& color);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    void text(const std::string& text);
    void renderTextura(SDL_Texture* texture, SDL_Rect& src_clip, 
                                                        SDL_Rect& render_clip);
    SDL_Texture* texturaDesdeSuperficie(SDL_Surface* surface);
    SDL_Texture* loadImage(const std::string& path);
private:
    SDL_Renderer* renderer;
    EntornoGrafico& entorno;
    SDL_Color color = {};
    int xoff = 0;
    int yoff = 0;
};

#endif
