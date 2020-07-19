#include "AnimacionOchoDirecciones.h"
#include <string>
#include "../modelo/parsers/AnimacionParser.h"

AnimacionOchoDirecciones::AnimacionOchoDirecciones(AnimacionParser& parser): 
                                                    AnimacionBase(parser) {
    accion = parser.getEstadoInicial();
    direccion = parser.getDireccionInicial();
}

void AnimacionOchoDirecciones::getMascara(SDL_Rect& mascara, int columna, int delta_x, int delta_y) {
    esta_quieto = (delta_x == 0 && delta_y == 0);
    nuevoEstado(delta_x, delta_y);
    AnimacionBase::getMascara(mascara, columna, delta_x, delta_y);   
}

void AnimacionOchoDirecciones::nuevoEstado(int delta_x, int delta_y) {
    std::string direccion_h;
    std::string direccion_v;
    if (delta_y > 0)
        direccion_v = ANIMACION_ABAJO;
    else if (delta_y < 0)
        direccion_v = ANIMACION_ARRIBA;
    if (delta_x > 0) 
        direccion_h = ANIMACION_DERECHA;
    else if (delta_x < 0)
        direccion_v = ANIMACION_IZQUIERDA;
    if (direccion_h.size() && direccion_v.size())
        direccion = direccion_h + "-" + direccion_v;
    else if (direccion_h.size())
        direccion = direccion_h;
    else if (direccion_v.size())
        direccion = direccion_v;
}
