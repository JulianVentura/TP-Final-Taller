#ifndef ESCENA_H
#define ESCENA_H

#include "IRendereable.h"
#include "Camara.h"
#include "MapaVista.h"
#include "CapaFrontal.h"
#include "Obstaculo.h"

class Escena: public IRendereable {
public:
    Escena(EntornoGrafico& entorno, Camara& camara, MapaVista& mapa, 
                CapaFrontal& capaFrontal, LibreriaConjuntoTiles& conjuntoTiles);
    void render() override;
    void actualizar(unsigned int delta_t) override;

private:
    Camara& camara;
    MapaVista& mapa;
    CapaFrontal& capaFrontal;
    LibreriaConjuntoTiles& conjuntoTiles;
};
#endif
