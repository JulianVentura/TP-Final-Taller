#include "EntornoGrafico.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ErrorGrafico.h"
#include "Ventana.h"

EntornoGrafico::EntornoGrafico() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
        throw ErrorGrafico("No se pudo inicializar video %s\n", SDL_GetError());
}

EntornoGrafico::~EntornoGrafico() {
    if (is_img_enabled) IMG_Quit();
    if (is_ttf_enabled) {
        TTF_CloseFont(font);
        TTF_Quit();
    }
    SDL_Quit();
}

void EntornoGrafico::run() {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            ventana->manejarEvento(e);
        }
        ventana->render();
    }
}

void EntornoGrafico::addRenderable(IRenderable* renderable) {
    renderable->setRenderer(renderer);
    renderable->setVentana(ventana);
}

void EntornoGrafico::setVentana(Ventana* ventana) {
    this->ventana = ventana;
}

void EntornoGrafico::enableImg() {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) 
        throw ErrorGrafico("No se pudo iniciar PNG %s\n", IMG_GetError());
    is_img_enabled = true;
}

void EntornoGrafico::enableTtf() {
    if (TTF_Init() == -1) 
        throw ErrorGrafico("No se pudo iniciar TTF %s\n", TTF_GetError());
    is_ttf_enabled = true;
}

static SDL_Surface* superficieDeImagenColorKey(const std::string& path, 
                                                        SDL_Color* color) {
    SDL_Surface* superficie = IMG_Load(path.c_str());
    if (!superficie) 
        throw ErrorGrafico("No se pudo cargar imagen %s: Error %s\n", 
                                                path.c_str(), IMG_GetError());
    auto key = SDL_MapRGB(superficie->format, color->r, color->g, color->g);
    SDL_SetColorKey(superficie, SDL_TRUE, key);
    return superficie;
}
SDL_Texture* EntornoGrafico::loadImagen(const std::string& path, 
                                            SDL_Color* key_color, bool cache) {
    if (!is_img_enabled) enableImg();
    if (cache && textures.count(path) > 0) return textures[path];
    SDL_Surface* superficie = superficieDeImagenColorKey(path, key_color);
    SDL_Texture* img_texture = renderer->texturaDesdeSuperficie(superficie);
    SDL_FreeSurface(superficie);
    textures[path] = img_texture;
    return textures[path];
}

SDL_Texture* EntornoGrafico::loadImagen(const std::string& path, bool cache) {
    if (!is_img_enabled) enableImg();
    if (cache && textures.count(path) > 0) return textures[path]; // Puede traer problemas
    SDL_Texture* img_texture = renderer->texturaDesdeArchivoImagen(path);
    textures[path] = img_texture;
    return textures[path];
}

void EntornoGrafico::loadFont(const std::string& path, int size) {
    if (!is_ttf_enabled) enableTtf();
    font = TTF_OpenFont(path.c_str(), size);
    if (!font) 
        throw ErrorGrafico("No se pudo cargar la fuente %s: Error %s\n", 
                                                path.c_str(), TTF_GetError());
}

TTF_Font* EntornoGrafico::getFont() {
    return font;
}
