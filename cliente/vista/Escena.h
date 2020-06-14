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
    void actualizar() override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Camara camara;
    PersonajeVista personaje;
    MapaVista mapa;
};


#endif