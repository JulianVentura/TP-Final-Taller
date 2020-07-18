#include "Escena.h"
#include "EntidadVista.h"
#include "LibreriaConjuntoTiles.h"
#include "CapaFrontal.h"

#define RADIO 16.0f
SDL_Rect frontera = {};
Escena::Escena(EntornoGrafico& entorno, Camara& camara, MapaVista& mapa, 
        CapaFrontal& capaFrontal, LibreriaConjuntoTiles& conjuntoTiles): 
            camara(&camara),
            mapa(&mapa),
            capaFrontal(&capaFrontal),
            conjuntoTiles(&conjuntoTiles) {
    entorno.agregarRendereable(this);
}

Escena& Escena::operator=(const Escena&& otro) {
    this->camara = otro.camara;
    this->capaFrontal = otro.capaFrontal;
    this->conjuntoTiles = conjuntoTiles;
    this->mapa = otro.mapa;
    this->renderer = otro.renderer;
    this->ventana = otro.ventana;
    return *this;
}

void Escena::render() {
    camara->centrar(renderer, mapa->getAnchoTile(), RADIO);
    camara->getFrontera(frontera);
    int columnas_visibles = frontera.w / mapa->getAnchoTile() + 1;
    int filas_visibles = frontera.h / mapa->getAltoTile() + 1;
    int columna_inicial = frontera.x / mapa->getAnchoTile();
    int fila_inicial = frontera.y / mapa->getAltoTile();

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
