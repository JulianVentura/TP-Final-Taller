#include "EntornoGrafico.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ErrorGrafico.h"
#include "Ventana.h"

EntornoGrafico::EntornoGrafico() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        throw ErrorGrafico("No se pudo inicializar video %s\n", SDL_GetError());
}

EntornoGrafico::~EntornoGrafico() {
    for (auto& texture: textures) {
        SDL_DestroyTexture(texture.second);
    }
    TTF_CloseFont(font);
    if (is_img_enabled) IMG_Quit();
    if (is_ttf_enabled) TTF_Quit();
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

SDL_Texture* EntornoGrafico::loadImagen(const std::string& path, 
        SDL_Rect* render_clip, SDL_Color* key_color) {
    if (!is_img_enabled) enableImg();
    if (textures.count(path) > 0) return textures[path];
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface) 
        throw ErrorGrafico("No se pudo cargar imagen %s: Error %s\n", 
                                                path.c_str(), IMG_GetError());
    if (key_color)
        SDL_SetColorKey(loaded_surface, SDL_TRUE, 
        SDL_MapRGB(
            loaded_surface->format, 
            key_color->r, 
            key_color->g, 
            key_color->g
        ));
    SDL_Texture* img_texture = renderer->textureFromSurface(loaded_surface, 
                                                                render_clip);
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