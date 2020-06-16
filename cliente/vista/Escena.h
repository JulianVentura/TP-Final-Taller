#ifndef ESCENA_H
#define ESCENA_H
#include "IRendereable.h"
#include "IInteractivo.h"
#include "Camara.h"
#include "MapaVista.h"
#include "PersonajeVista.h"

class Escena: public IRendereable, public IInteractivo {
public:
    explicit Escena(EntornoGrafico& entorno);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Camara camara;
    Personaje personajeModelo;
    PersonajeVista personaje;
    Personaje enemigoModelo;
    MovibleVista enemigo;
    MapaVista mapa;
};

#endif
