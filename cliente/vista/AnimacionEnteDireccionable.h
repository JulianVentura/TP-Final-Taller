#ifndef ANIMACIONENTEDIRECCIONABLE_H
#define ANIMACIONENTEDIRECCIONABLE_H

#include "Animacion.h"
#include <string>

#define ANIMACION_BASE    "base"
#define ANIMACION_ARRIBA    "Arriba"
#define ANIMACION_ABAJO     "Abajo"
#define ANIMACION_DERECHA   "Derecha"
#define ANIMACION_IZQUIERDA "Izquierda"

class AnimacionEnteDireccionable: public Animacion {
public:
    AnimacionEnteDireccionable(EntidadParser& parser, 
                                        const std::string& animacion_inicial);
    virtual ~AnimacionEnteDireccionable() = default;
    void actualizarEstado(unsigned int delta_t, int delta_x, int delta_y);

private:
    void nuevoEstado(int delta_x, int delta_y);
};

#endif
