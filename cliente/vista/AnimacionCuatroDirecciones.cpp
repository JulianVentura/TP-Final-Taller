#include "AnimacionCuatroDirecciones.h"
#include <string>
#include "../modelo/parsers/AnimacionParser.h"

#define RANGO 3 * M_PI_4 / 4

AnimacionCuatroDirecciones::AnimacionCuatroDirecciones(AnimacionParser& parser): 
                                                    AnimacionBase(parser) {
}

std::string AnimacionCuatroDirecciones::getDireccion(int delta_x, int delta_y) {
    std::string direccion = "";
    if (delta_x == 0) {
        if (delta_y > 0)
            direccion = ANIMACION_ABAJO;
        else if (delta_y < 0)
            direccion = ANIMACION_ARRIBA;    
        return direccion;
    }
    float angulo = atan2(-delta_y, delta_x);
    if (angulo < 0) angulo += 2 * M_PI;
    if (3 * M_PI_2 - RANGO <= angulo && angulo <= 3 * M_PI_2 + RANGO) 
        direccion = ANIMACION_ABAJO;
    if (M_PI_2 - RANGO <= angulo && angulo <= M_PI_2 + RANGO)
        direccion = ANIMACION_ARRIBA;
    if ((0 <= angulo && angulo <= RANGO) || 
        (2 * M_PI - RANGO <= angulo && angulo <= 2 * M_PI))
        direccion = ANIMACION_DERECHA;
    if (M_PI - RANGO <= angulo && angulo <= M_PI + RANGO) 
        direccion = ANIMACION_IZQUIERDA;
    return direccion;
}

bool AnimacionCuatroDirecciones::estaQuieto(int delta_x, int delta_y) {
    return delta_x == 0 && delta_y == 0;
}
