#ifndef ANIMACIONCUATRODIRECICONES_H
#define ANIMACIONCUATRODIRECICONES_H

#include "AnimacionBase.h"
#include <string>

#define ANIMACION_BASE      "base"
#define ANIMACION_ARRIBA    "Arriba"
#define ANIMACION_ABAJO     "Abajo"
#define ANIMACION_DERECHA   "Derecha"
#define ANIMACION_IZQUIERDA "Izquierda"

class AnimacionCuatroDirecciones: public AnimacionBase {
public:
    AnimacionCuatroDirecciones(AnimacionParser& parser);
    virtual ~AnimacionCuatroDirecciones() = default;
    std::string getDireccion(int delta_x, int delta_y) override;
    bool estaQuieto(int delta_x, int delta_y) override;
};
#endif
