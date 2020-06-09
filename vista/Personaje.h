#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "IRenderable.h"
#include "IInteractivo.h"
#include "ITargeteable.h"
#include "Imagen.h"

class Personaje: public IRenderable, public IInteractivo, public ITargeteable {
public:
    explicit Personaje(EntornoGrafico& entorno);
    void render() override;
    void actualizar() override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Imagen imagen;
    int velocidadY = 0;
    int velocidadX = 0;
};

#endif
