#ifndef IMAGEN_H
#define IMAGEN_H

#include "EntornoGrafico.h"
#include "Ventana.h"
#include <string>

class Imagen: public IRendereable, public IDimensionable {
public:
    Imagen() = default;
    virtual ~Imagen() = default;
    /**
     * @brief Crea una imagen desde el archivo que corresponde a ruta.
     * @throw ErrorGrafico en caso de error.
     */
    Imagen(EntornoGrafico& entorno, const std::string& ruta);

    /**
     * @brief Crea una imagen desde el archivo que corresponde a ruta. Se 
     * borrarán los pixeles del color que se pasa por parámetro.
     * @throw ErrorGrafico en caso de error.
     */
    Imagen(EntornoGrafico& entorno, const std::string& ruta, SDL_Color* color);
    void render() override;
    void renderExpandido();
    void setPosicion(int x, int y);
    virtual int getAncho() override;
    virtual int getAlto() override;
    void setAncho(int ancho);
    void setAlto(int alto);
    
    /**
     * @brief Determina la porción de imagen que se va a renderear.
     */
    void setMascara(int x, int y, int ancho, int alto);
    void setMascara(SDL_Rect& mascara);

private:
    void iniciarDimension(SDL_Texture* texture);
    EntornoGrafico* entorno;
    SDL_Texture* textura = NULL;
    SDL_Rect mascara = {};
    SDL_Rect render_mascara = {};
};

#endif
