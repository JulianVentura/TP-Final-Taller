#ifndef MOVIBLEVISTA_H
#define MOVIBLEVISTA_H
#include "AnimacionEnteDireccionable.h"
#include "IObstruible.h"
#include "Imagen.h"
#include "Personaje.h"

class MovibleVista: public IObstruible {
public:
    MovibleVista(EntornoGrafico& entorno, Personaje& modelo, std::string& id);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    
private:
    Imagen imagen;
    AnimacionEnteDireccionable animacion;
    std::string ultimo_estado;
    
protected:
    Personaje& personajeModelo;
};

#endif
