#ifndef IMAGEN_H
#define IMAGEN_H

#include "EntornoGrafico.h"
#include "Ventana.h"
#include <string>

class Imagen: public IRenderable {
public:
    Imagen() = default;
    Imagen(EntornoGrafico& entorno, const std::string& path);
    Imagen(EntornoGrafico& entorno, const std::string& path, SDL_Color* color);
    void render() override;
    void setPosicion(int x, int y);
    int getAncho();
    int getAlto();
    void setAncho(int ancho);
    void setAlto(int alto);
    void setClip(int x, int y, int ancho, int alto);
private:
    void iniciarDimension(SDL_Texture* texture);
    EntornoGrafico* entorno;
    SDL_Texture* texture;
    SDL_Rect src_clip = {};
    SDL_Rect render_clip = {};
};

#endif
