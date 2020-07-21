#include "AnimacionOchoDirecciones.h"
#include <cmath>
#include <string>
#include "../modelo/parsers/AnimacionParser.h"

#define M_PI_8 M_PI_4 / 2

AnimacionOchoDirecciones::AnimacionOchoDirecciones(AnimacionParser& parser): 
                                                    AnimacionBase(parser) {
}

std::string AnimacionOchoDirecciones::getDireccion(int delta_x, int delta_y) {
    std::string direccion;
    std::string direccion_h;
    std::string direccion_v;
    if (delta_x == 0) {
        if (delta_y > 0)
            direccion_v = ANIMACION_ABAJO;
        else if (delta_y < 0)
            direccion_v = ANIMACION_ARRIBA;    
        return direccion_v;
    }
    float angulo = atan2(-delta_y, delta_x);
    if (angulo < 0) angulo += 2 * M_PI;
    if (M_PI + M_PI_8 <= angulo && angulo <= 2 * M_PI - M_PI_8) 
        direccion_v = ANIMACION_ABAJO;
    if (M_PI_8 <= angulo && angulo <= M_PI - M_PI_8)
        direccion_v = ANIMACION_ARRIBA;
    if ((0 <= angulo && angulo <= M_PI_2 - M_PI_8) || 
        (3 * M_PI_2 + M_PI_8 <= angulo && angulo <= 2 * M_PI))
        direccion_h = ANIMACION_DERECHA;
    if (M_PI_2 + M_PI_8 <= angulo && angulo <= 3 * M_PI_2 - M_PI_8) 
        direccion_h = ANIMACION_IZQUIERDA;
    if (direccion_h.size() && direccion_v.size())
        direccion = direccion_h + "-" + direccion_v;
    else if (direccion_h.size())
        direccion = direccion_h;
    else if (direccion_v.size())
        direccion = direccion_v;
    return direccion;
}

bool AnimacionOchoDirecciones::estaQuieto(int delta_x, int delta_y) {
    return delta_x == 0 && delta_y == 0;
}
