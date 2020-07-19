#include "AnimacionCuatroDirecciones.h"
#include <string>
#include "../modelo/parsers/AnimacionParser.h"

AnimacionCuatroDirecciones::AnimacionCuatroDirecciones(AnimacionParser& parser): 
                                                    AnimacionBase(parser) {
    accion = parser.getEstadoInicial();
    direccion = parser.getDireccionInicial();
}

void AnimacionCuatroDirecciones::getMascara(SDL_Rect& mascara,int columna, int delta_x, int delta_y) {
    esta_quieto = (delta_x == 0 && delta_y == 0);
    nuevoEstado(delta_x, delta_y);
    AnimacionBase::getMascara(mascara, columna, delta_x, delta_y);   
}

void AnimacionCuatroDirecciones::nuevoEstado(int delta_x, int delta_y) {
    if (delta_y > 0)
        direccion = ANIMACION_ABAJO;
    else if (delta_y < 0)
        direccion = ANIMACION_ARRIBA;
    else if (delta_x > 0) 
        direccion = ANIMACION_DERECHA;
    else if (delta_x < 0)
        direccion = ANIMACION_IZQUIERDA;
}
