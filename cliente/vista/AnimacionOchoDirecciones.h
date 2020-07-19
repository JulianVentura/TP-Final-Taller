#ifndef ANIMACIONOCHODIRECICONES_H
#define ANIMACIONOCHODIRECICONES_H

#include "Animacion.h"
#include <string>

#define ANIMACION_BASE      "base"
#define ANIMACION_ARRIBA    "Arriba"
#define ANIMACION_ABAJO     "Abajo"
#define ANIMACION_DERECHA   "Derecha"
#define ANIMACION_IZQUIERDA "Izquierda"

class AnimacionOchoDirecciones: public AnimacionBase {
public:
    AnimacionOchoDirecciones(AnimacionParser& parser);
    virtual ~AnimacionOchoDirecciones() = default;
    void getMascara(SDL_Rect& mascara, int columna, int delta_x, int delta_y) override;

private:
    void nuevoEstado(int delta_x, int delta_y);
};

#endif
