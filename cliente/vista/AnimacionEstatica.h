#ifndef ANIMACIONESTATICA_H
#define ANIMACIONESTATICA_H
#include "AnimacionBase.h"

class AnimacionEstatica: public AnimacionBase {
public:
    AnimacionEstatica(int ancho, int alto);
    virtual ~AnimacionEstatica() = default;
    void getMascara(SDL_Rect& mascara, int columna, int delta_x, int delta_y) override;
    int getColumnas() override;
    int getTiempoPorCiclo() override;
    int getTiempoPorCuadro() override;

private:
    int ancho;
    int alto;
};
#endif
