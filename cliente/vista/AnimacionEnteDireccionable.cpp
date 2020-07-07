#include "AnimacionEnteDireccionable.h"
#include <string>

AnimacionEnteDireccionable::AnimacionEnteDireccionable(EntidadParser& parser,
        const std::string& animacion_inicial): 
        Animacion(parser, animacion_inicial) {
    setAccion("caminar");
}

void AnimacionEnteDireccionable::actualizarEstado(unsigned int delta_t, 
                                                    int delta_x, int delta_y) {
    esta_quieto = (delta_x == 0 && delta_y == 0);
    setAnimacion("base");
    nuevoEstado(delta_x, delta_y);
    actualizar(delta_t);
}

void AnimacionEnteDireccionable::nuevoEstado(int delta_x, int delta_y) {
    if (delta_x > 0) 
        direccion = ANIMACION_DERECHA;
    else if (delta_x < 0) 
        direccion = ANIMACION_IZQUIERDA;
    else if (delta_y > 0) 
        direccion = ANIMACION_ABAJO;
    else if (delta_y < 0) 
        direccion = ANIMACION_ARRIBA;
}
