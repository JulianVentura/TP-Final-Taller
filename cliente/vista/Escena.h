#ifndef ESCENA_H
#define ESCENA_H
#include "IRendereable.h"
#include "IInteractivo.h"
#include "Camara.h"
#include "MapaVista.h"
#include "PersonajeVista.h"
#include "CapaFrontal.h"
#include "Obstaculo.h"

class Escena: public IRendereable, public IInteractivo {
public:
    explicit Escena(EntornoGrafico& entorno, Camara& camara, MapaVista& mapa, 
                CapaFrontal& capaFrontal, LibreriaConjuntoTiles& conjuntoTiles);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Camara& camara;
    MapaVista& mapa;
    CapaFrontal& capaFrontal;
    LibreriaConjuntoTiles& conjuntoTiles;
    // Personaje personajeModelo;
    // PersonajeVista personaje;
    // Personaje enemigoModelo;
    // MovibleVista enemigo;
};
#endif
