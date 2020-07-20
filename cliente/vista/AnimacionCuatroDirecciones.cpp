#include "AnimacionCuatroDirecciones.h"
#include <string>
#include "../modelo/parsers/AnimacionParser.h"

AnimacionCuatroDirecciones::AnimacionCuatroDirecciones(AnimacionParser& parser): 
                                                    AnimacionBase(parser) {
}

std::string AnimacionCuatroDirecciones::getDireccion(int delta_x, int delta_y) {
    printf("se llama al get dir de animac 4 dire\n");
    std::string direccion;
    if (delta_y > 0)
        direccion = ANIMACION_ABAJO;
    else if (delta_y < 0)
        direccion = ANIMACION_ARRIBA;
    else if (delta_x > 0) 
        direccion = ANIMACION_DERECHA;
    else if (delta_x < 0)
        direccion = ANIMACION_IZQUIERDA;
    return direccion;
}

bool AnimacionCuatroDirecciones::estaQuieto(int delta_x, int delta_y) {
    return delta_x == 0 && delta_y == 0;
}
