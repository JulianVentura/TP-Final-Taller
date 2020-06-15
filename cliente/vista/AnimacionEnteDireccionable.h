#ifndef ANIMACIONENTEDIRECCIONABLE_H
#define ANIMACIONENTEDIRECCIONABLE_H

#include "Animacion.h"

#define ARRIBA    "Arriba"
#define ABAJO     "Abajo"
#define DERECHA   "Derecha"
#define IZQUIERDA "Izquierda"
#define QUIETO    "-Quieto"

class AnimacionEnteDireccionable: public Animacion {
public:
    AnimacionEnteDireccionable() = default;
    AnimacionEnteDireccionable(Imagen& imagen, mascaras_t mascaras, 
                                        const std::string& animacion_inicial);
    void actualizarEstado(unsigned int delta_t, int delta_x, int delta_y);

private:
    void nuevoEstado(int delta_x, int delta_y);
    std::string animacion_actual;
};

#endif