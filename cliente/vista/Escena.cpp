#include "Escena.h"
#include "MovibleVista.h"
#include "LibreriaConjuntoTiles.h"
#include "CapaFrontal.h"

#define RADIO 16.0f

Escena::Escena(EntornoGrafico& entorno, Camara& camara, MapaVista& mapa, 
        CapaFrontal& capaFrontal, LibreriaConjuntoTiles& conjuntoTiles): 
            camara(camara),
            mapa(mapa),
            capaFrontal(capaFrontal),
            conjuntoTiles(conjuntoTiles) {
    entorno.agregarRendereable(this);
}

void Escena::render() {
    camara.centrar(renderer, mapa.getAnchoTile(), RADIO);
    mapa.render();
    capaFrontal.render();
    camara.reiniciar(renderer);
}

void Escena::actualizar(unsigned int delta_t) {
    mapa.actualizar(delta_t);
    capaFrontal.actualizar(delta_t);
}
