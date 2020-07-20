#include "AnimacionEstatica.h"
#include <string>
#include "../modelo/parsers/AnimacionParser.h"

AnimacionEstatica::AnimacionEstatica(int ancho, int alto): ancho(ancho), alto(alto) {}

void AnimacionEstatica::getMascara(Animacion& animacion, std::string& direccion_vieja, 
                                        SDL_Rect& mascara, int delta_x, int delta_y) {
    mascara = {0, 0, ancho, alto}; 
}

int AnimacionEstatica::getColumnas(std::string& accion, std::string& direccion) {
    return 0;
}

int AnimacionEstatica::getTiempoPorCiclo() {
    return 0;
}
int AnimacionEstatica::getTiempoPorCuadro() {
    return 0;
}
