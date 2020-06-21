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
    /**
     * @brief Pinta toda la pantalla con el color seleccionado con setColor. 
     */
    void limpiar();

    void limpiarTextura(SDL_Texture* textura);
    /**
     * @brief Muestra en pantalla lo que se fue rendereando.
     * @post se reicinician las transformaciones de escalado y desplazamiento.
     */
    void presentar();

    /**
     * @brief Transforma el plano aplicando un desplazamiento en x e y.
     * Las transformaciones de desplazamiento son acumulaticas.
     */
    void desplazar(int desplazamientoX, int desplazamientoY);

    void rect(SDL_Rect& rect);
    void rect(int x, int y, int ancho, int alto);
    void rectSolido(SDL_Rect& rect);
    void rectSolido(int x, int y, int ancho, int alto);
    void linea(int x1, int y1, int x2, int y2);
    
    /**
     * @brief Determina el color que va a utilizar el renderer para el resto de
     * métodos. Aplicable a: limpiar, rect, rectSolido, linea, texto.
     */
    void setColor(SDL_Color& color);
    void setColor(Uint8 escala);
    void setColor(Uint8 rojo, Uint8 verde, Uint8 azul);
    void setColor(Uint8 rojo, Uint8 verde, Uint8 azul, Uint8 alpha);
    /**
     * @brief Determina el color que va a utilizar el renderer para el resto de
     * métodos.
     * @param hexa cadena con el color en forma hexadecimal, de la forma:
     * #RRGGBB, donde RR, GG, BB, son números hexadecimales que determinan la 
     * combinación de rojo, verde, azul, respectivamente. 
     * Aplicable a: limpiar, rect, rectSolido, linea, texto.
     */
    void setColor(std::string hexa);
    
    SDL_Color colorDesdeHexa(std::string hexa);
    
    /**
     * @brief Muestra texto en la pantalla. Opcionalmente se le puede establecer
     * un x e y, indicando dónde se mostrará, donde esta es la esquina superior 
     * izquierda.
     * @pre El EntornoGrafico cuenta con una fuente establecida.
     */
    void texto(const std::string& text);
    void texto(const std::string& text, int x, int y);
    void textoATextura(SDL_Texture* textura, const std::string& text,
     int x, int y);
    
    /**
     * @brief Muestra en pantalla la textura.
     * @param origen_mascara: Porción de la textura que se mostrará. NULL para 
     * la textura completa.
     * @param render_mascara: Contiene la posición donde se mostrará la textura
     * y el ancho y alto que ocupará. NULL para ocupar toda la pantalla.
     */
    void renderTextura(SDL_Texture* texture, SDL_Rect& origen_mascara, 
                                        SDL_Rect& render_mascara); // Maybe x, y
    
    SDL_Texture* textura(int ancho, int alto);

    /**
     * @brief Dada una superficie, se crea una textura.
     * @throw ErrorGrafico en caso de que falle.
     */
    SDL_Texture* texturaDesdeSuperficie(SDL_Surface* superficie);

    /**
     * @brief Dada una ruta correspondiente a un archivo de imagen, se creará la
     * textura correspondiente.
     * @throw ErrorGrafico en caso de que falle.
     */
    SDL_Texture* texturaDesdeArchivoImagen(const std::string& ruta);
    
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
