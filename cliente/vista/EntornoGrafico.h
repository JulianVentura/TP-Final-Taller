#ifndef ENTORNOGRAFICO_H
#define ENTORNOGRAFICO_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Ventana;
class Renderer;
class IRendereable;

class EntornoGrafico {
public:
    EntornoGrafico();
    EntornoGrafico(const EntornoGrafico&) = delete;
    EntornoGrafico(EntornoGrafico&) = delete;
    ~EntornoGrafico();
    /**
     * @brief Asocia la ventana al entorno.
     */
    void setVentana(Ventana* ventana);

    /**
     * @brief A rendereable se le asignan tanto el Renderer como la Ventana.
     * @post rendereable podrá usar el renderer y la ventana.
     */
    void agregarRendereable(IRendereable* rendereable);
    
    /**
     * @brief Carga un archivo de imagen desde ruta. 
     * Si la imagen fue previante cargada, se devolverá la textura previamente 
     * cargada, salvo que cache sea false.
     * @throw ErrorGrafico en caso de error.
     */
    SDL_Texture* cargarImagen(const std::string& ruta, bool cache = true);
    
    /**
     * @brief Carga un archivo de imagen desde ruta. Se borrarán los pixeles 
     * del color que se pasa por parámetro.
     * Si la imagen fue previante cargada, se devolverá la textura previamente 
     * cargada, salvo que cache sea false.
     * @throw ErrorGrafico en caso de error.
     */
    SDL_Texture* cargarImagen(const std::string& ruta, SDL_Color* color, 
                                                            bool cache = true);
    /**
     * @brief Carga desde un archivo una fuente y se establece como la fuente 
     * que utilizará el entorno.
     * @throw ErrorGrafico en caso de error.
     */
    void cargarFuente(const std::string& ruta, int size);
    TTF_Font* getFuente();

private:
    void enableImg();
    void enableTtf();
    Ventana* ventana;
    Renderer* renderer;
    bool is_img_enabled = false;
    bool is_ttf_enabled = false;
    TTF_Font* font;
    std::unordered_map<std::string, SDL_Texture*> textures;
    friend class Renderer;
};
#endif
