#ifndef MAPA_H
#define MAPA_H

#include "IRendereable.h"
#include "IInteractivo.h"
#include "Imagen.h"

class Mapa: public IRendereable, public IInteractivo, public IDimensionable {
public:
    explicit Mapa(EntornoGrafico& entorno);
    void render() override;
    void actualizar() override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Imagen imagen;
    int x = 0;
    int y = 0;
    int velocidadY = 0;
    int velocidadX = 0;
};


#endif
