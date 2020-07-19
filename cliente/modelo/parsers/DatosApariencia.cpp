#include "DatosApariencia.h"

bool DatosApariencia::operator==(const DatosApariencia &otro) const {
    return arma == otro.arma && casco == otro.casco && escudo == otro.escudo
    && armadura == otro.armadura && raza == otro.raza && clase == otro.clase &&
    estado == otro.estado && tipo == otro.tipo;
}
