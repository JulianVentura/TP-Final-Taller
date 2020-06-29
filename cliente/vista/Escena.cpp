#include "Escena.h"
#include "MovibleVista.h"
#include <fstream>
#include <algorithm>
#include <string>
#include "IObstruible.h"
#include "../modelo/MapaParser.h"
#include "../modelo/LibreriaConjuntoTileParser.h"
#include "LibreriaConjuntoTiles.h"
#include "../modelo/ObstaculoParser.h"
#include "../modelo/CapasParser.h"
#include "ErrorGrafico.h"
#include "CapaFrontal.h"
#define RADIO 16.0f

#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

void Escena::manejarEvento(const SDL_Event& event) {
}

void Escena::actualizar(unsigned int delta_t) {
    mapa.actualizar(delta_t);
    capaFrontal.actualizar(delta_t);
}
