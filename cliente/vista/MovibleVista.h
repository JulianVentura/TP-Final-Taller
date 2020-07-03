#ifndef MOVIBLEVISTA_H
#define MOVIBLEVISTA_H
#include "AnimacionEnteDireccionable.h"
#include "IObstruible.h"
#include "Imagen.h"
#include "../modelo/Movible.h"
#include <string>

class MovibleVista: public IObstruible {
public:
    MovibleVista(EntornoGrafico& entorno, Movible& modelo);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    
private:
    Imagen imagen;
    AnimacionEnteDireccionable animacion;
    std::string ultimo_estado;
    Movible& modelo;
};

#endif
