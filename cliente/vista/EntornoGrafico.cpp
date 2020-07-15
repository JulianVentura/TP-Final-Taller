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
    for (auto& textura: textures)
        SDL_DestroyTexture(textura.second);
    
    SDL_Quit();
}

void EntornoGrafico::agregarRendereable(IRendereable* rendereable) {
    rendereable->setRenderer(renderer);
    rendereable->setVentana(ventana);
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

static SDL_Surface* superficieDeImagenColorKey(const std::string& ruta, 
                                                        SDL_Color* color) {
    SDL_Surface* superficie = IMG_Load(ruta.c_str());
    if (!superficie) 
        throw ErrorGrafico("No se pudo cargar imagen %s: Error %s\n", 
                                                ruta.c_str(), IMG_GetError());
    auto key = SDL_MapRGB(superficie->format, color->r, color->g, color->b);
    SDL_SetColorKey(superficie, SDL_TRUE, key);
    return superficie;
}
SDL_Texture* EntornoGrafico::cargarImagen(const std::string& ruta, 
                                            SDL_Color* color, bool cache) {
    if (!is_img_enabled) enableImg();
    if (cache && textures.count(ruta) > 0) return textures[ruta];
    SDL_Surface* superficie = superficieDeImagenColorKey(ruta, color);
    SDL_Texture* img_texture = renderer->texturaDesdeSuperficie(superficie);
    SDL_FreeSurface(superficie);
    textures[ruta] = img_texture;
    return textures[ruta];
}

SDL_Texture* EntornoGrafico::cargarImagen(const std::string& ruta, bool cache) {
    if (!is_img_enabled) enableImg();
    if (cache && textures.count(ruta) > 0) return textures[ruta];
    SDL_Texture* img_texture = renderer->texturaDesdeArchivoImagen(ruta);
    textures[ruta] = img_texture;
    return textures[ruta];
}

void EntornoGrafico::cargarFuente(const std::string& ruta, int size) {
    if (!is_ttf_enabled) enableTtf();
    font = TTF_OpenFont(ruta.c_str(), size);
    if (!font) 
        throw ErrorGrafico("No se pudo cargar la fuente %s: Error %s\n", 
                                                ruta.c_str(), TTF_GetError());
}

TTF_Font* EntornoGrafico::getFuente() {
    return font;
}

