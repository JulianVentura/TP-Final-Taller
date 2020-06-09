#ifndef MAPA_H
#define MAPA_H

#include "IRenderable.h"
#include "IInteractivo.h"
#include "Imagen.h"

class Mapa: public IRenderable, public IInteractivo {
public:
    explicit Mapa(EntornoGrafico& entorno);
    void render() override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Imagen imagen;
    int x = 0;
    int y = 0;
    int velocidadY = 0;
    int velocidadX = 0;
};


#endif
