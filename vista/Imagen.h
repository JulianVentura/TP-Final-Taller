#ifndef IMAGEN_H
#define IMAGEN_H

#include "EntornoGrafico.h"
#include "Ventana.h"
#include <string>

class Imagen: public IRenderable {
public:
    Imagen() = default;
    Imagen(EntornoGrafico& entorno, std::string& path, SDL_Color* key_color = NULL);
    void render() override;
    void setPosicion(int x, int y);
    int getAncho();
    int getAlto();
private:
    EntornoGrafico* entorno;
    SDL_Texture* texture;
    SDL_Rect src_clip;
    SDL_Rect render_clip;
};

#endif
