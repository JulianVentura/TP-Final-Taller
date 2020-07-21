#include "Escena.h"
#include "EntidadVista.h"
#include "LibreriaConjuntoTiles.h"
#include "CapaFrontal.h"

#define RADIO 16.0f
#define BUFFER 16

Escena::Escena(EntornoGrafico& entorno, Camara& camara, MapaVista& mapa, 
        CapaFrontal& capaFrontal, LibreriaConjuntoTiles& conjuntoTiles): 
            camara(&camara),
            mapa(&mapa),
            capaFrontal(&capaFrontal),
            conjuntoTiles(&conjuntoTiles) {
    entorno.agregarRendereable(this);
}

void Escena::render() {
    camara->centrar(renderer, mapa->getAnchoTile(), RADIO);
    camara->getFrontera(frontera);
    int columnas_visibles = frontera.w / mapa->getAnchoTile() + BUFFER;
    int filas_visibles = frontera.h / mapa->getAltoTile() + BUFFER;
    int columna_inicial = frontera.x / mapa->getAnchoTile() - BUFFER / 2;
    int fila_inicial = frontera.y / mapa->getAltoTile() - BUFFER / 2;

    frontera = { columna_inicial, fila_inicial, 
                columnas_visibles, filas_visibles };
    mapa->setFrontera(frontera);
    mapa->render();
    capaFrontal->setFrontera(frontera);
    capaFrontal->render();
    camara->reiniciar(renderer);
}

void Escena::actualizar(unsigned int delta_t) {
    mapa->actualizar(delta_t);
    capaFrontal->actualizar(delta_t);
}
