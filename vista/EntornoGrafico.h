#ifndef ENTORNOGRAFICO_H
#define ENTORNOGRAFICO_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Ventana;
class Renderer;
class IRenderable;

class EntornoGrafico {
public:
    EntornoGrafico();
    ~EntornoGrafico();
    void run();
    void setVentana(Ventana* ventana);
    void addRenderable(IRenderable* renderable);
    SDL_Texture* loadImagen(const std::string& path, bool cache = true);
    SDL_Texture* loadImagen(const std::string& path, SDL_Color* key_color, 
                                                            bool cache = true);
    void loadFont(const std::string& path, int size);
    TTF_Font* getFont();
private:
    void enableImg();
    void enableTtf();
    bool is_img_enabled = false;
    bool is_ttf_enabled = false;
    std::unordered_map<std::string, SDL_Texture*> textures;
    TTF_Font* font;
    Ventana* ventana;
    Renderer* renderer;
    friend class Renderer;
};
#endif
