#include "AnimacionEnteDireccionable.h"

AnimacionEnteDireccionable::AnimacionEnteDireccionable(Imagen& imagen, 
    mascaras_t mascaras, const std::string& animacion_inicial): Animacion(
                                        imagen, mascaras, animacion_inicial) {
    animacion_actual = animacion_inicial;
}

void AnimacionEnteDireccionable::actualizarEstado(unsigned int delta_t, 
                                                    int delta_x, int delta_y) {
    std::string agregado;
    if (delta_x == 0 && delta_y == 0)
        agregado = QUIETO;

    nuevoEstado(delta_x, delta_y);
    setAnimacion(animacion_actual + agregado);
    actualizar(delta_t);
}

void AnimacionEnteDireccionable::nuevoEstado(int delta_x, int delta_y) {
    if (delta_x > 0) 
        animacion_actual = DERECHA;
    else if (delta_x < 0) 
        animacion_actual = IZQUIERDA;
    else if (delta_y > 0) 
        animacion_actual = ABAJO;
    else if (delta_y < 0) 
        animacion_actual = ARRIBA;
}
