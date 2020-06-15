#ifndef TILE_H
#define TILE_H

#include "IRendereable.h"
#include "Imagen.h"

class Tile: public IRendereable {
public:
    Tile(EntornoGrafico& entorno, Imagen* imagen, int x, int y);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void setMascara(int x, int y, int ancho, int alto);

private:
    Imagen* imagen;
    int x = 0;
    int y = 0;
    SDL_Rect mascara = {0, 0, 500, 500};
    static const int ANCHO_TILE = 500;
};

#endif
