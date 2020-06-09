#ifndef ESCENA_H
#define ESCENA_H
#include "IRenderable.h"
#include "IInteractivo.h"
#include "Camara.h"
#include "Mapa.h"
#include "Personaje.h"

class Escena: public IRenderable, public IInteractivo {
public:
    explicit Escena(EntornoGrafico& entorno);
    void render() override;
    void actualizar() override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Camara camara;
    Personaje personaje;
    Mapa mapa;
};


#endif
