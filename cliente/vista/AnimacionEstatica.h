#ifndef ANIMACIONESTATICA_H
#define ANIMACIONESTATICA_H
#include "AnimacionBase.h"

class AnimacionEstatica: public AnimacionBase {
public:
    AnimacionEstatica(int ancho, int alto);
    virtual ~AnimacionEstatica() = default;
void getMascara(Animacion& animacion, std::string& direccion_vieja,
                            SDL_Rect& mascara, int delta_x, int delta_y) override;
    int getColumnas(std::string& accion, std::string& direccion) override;
    int getTiempoPorCiclo() override;
    int getTiempoPorCuadro() override;

private:
    int ancho;
    int alto;
};
#endif
