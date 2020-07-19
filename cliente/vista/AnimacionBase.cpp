#include "AnimacionBase.h"
#include "AnimacionCuatroDirecciones.h"
#include "../modelo/parsers/AnimacionParser.h"
#include <string>

AnimacionBase::AnimacionBase(AnimacionParser& parser): parser(&parser), esta_quieto(false) {
    accion = this->parser->getEstadoInicial();
    tiempo_por_ciclo = this->parser->getTiempoEntreCiclo();
    tiempo_por_cuadro = this->parser->getTiempoPorCuadro();
}

void AnimacionBase::getMascara(SDL_Rect& mascara, int columna, int delta_x, int delta_y) {
    if (!parser) return;
    if (parser->getColumnas() == 0) return;
    if (esta_quieto) columna = 0;
    int guid = parser->getGuid(accion, direccion, columna, esta_quieto);
    int ancho = parser->getAncho();
    int alto = parser->getAlto();
    int fila = (guid - columna) / parser->getColumnas();
    mascara = { columna * ancho, fila * alto, ancho, alto };
}

int AnimacionBase::getColumnas() {
    if (!parser) return 0;
    return parser->getColumnas(accion, direccion);
}

int AnimacionBase::getTiempoPorCiclo() {
    return tiempo_por_ciclo;
}

int AnimacionBase::getTiempoPorCuadro() {
    return tiempo_por_cuadro;
}
