#include "AnimacionBase.h"
#include "Animacion.h"
#include "../modelo/parsers/AnimacionParser.h"

#include <string>

AnimacionBase::AnimacionBase(AnimacionParser& parser): parser(&parser) {
    tiempo_por_ciclo = this->parser->getTiempoEntreCiclo();
    tiempo_por_cuadro = this->parser->getTiempoPorCuadro();
}

void AnimacionBase::getMascara(Animacion& animacion, std::string& direccion_anterior, 
                                    SDL_Rect& mascara, int delta_x, int delta_y) {
    if (!parser) return;
    if (parser->getColumnas() == 0) return;
    std::string direccion(getDireccion(delta_x, delta_y));
    if (!direccion.size()) direccion = direccion_anterior;
    animacion.setMascara(parser, mascara, direccion, estaQuieto(delta_x, delta_y));
}

AnimacionParser* AnimacionBase::getParser() {
    return parser;
}

bool AnimacionBase::estaQuieto(int delta_x, int delta_y) {
    return false;
}

int AnimacionBase::getColumnas(std::string& accion, std::string& direccion) {
    if (!parser) return 0;
    return parser->getColumnas(accion, direccion);
}

int AnimacionBase::getTiempoPorCiclo() {
    return tiempo_por_ciclo;
}

int AnimacionBase::getTiempoPorCuadro() {
    return tiempo_por_cuadro;
}


std::string AnimacionBase::getDireccion(int delta_x, int delta_y) {
    return "";
}
