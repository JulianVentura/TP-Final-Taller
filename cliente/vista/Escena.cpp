#include "Escena.h"
#include "MovibleVista.h"
#include <fstream>
#include <algorithm>
#include <string>
#include "IObstruible.h"
#include "MapaParser.h"
#include "LibreriaConjuntoTileParser.h"
#include "LibreriaConjuntoTiles.h"
#include "ObstaculoParser.h"
#include "CapasParser.h"

// TODO: provisorio
std::vector<IObstruible*> obstruibles;

std::string personaje_id("human");
std::string enemigo_id("golum");

Escena::Escena(EntornoGrafico& entorno){
    entorno.agregarRendereable(this);
    camara = Camara(&mapa, ventana);
    //camara.setObjetivo(personaje);
    std::ifstream fuente("assets/mapa.json");
    
    CapasParser capasParser(fuente);
    this->capasFrente = std::move(capasParser.getCapas());
    this->capasOrdenadas = std::move(capasParser.getCapasOrdenadas());
    fuente = std::ifstream("assets/mapa.json");

    LibreriaConjuntoTileParser libreriaConjuntoTileParser(fuente);
    this->conjuntosTiles = std::move(LibreriaConjuntoTiles(entorno, 
                                                libreriaConjuntoTileParser));

    fuente = std::ifstream("assets/mapa.json");

    ObstaculoParser obstaculoParser(fuente, capasFrente, conjuntosTiles);
    this->capasObstaculos = std::move(obstaculoParser.getCapasObstaculos());
    
    fuente = std::ifstream("assets/mapa.json");
    MapaParser mapaParser(fuente);
    mapa = std::move(MapaVista(entorno, mapaParser, conjuntosTiles));
    
    for (const auto& nombreCapa: capasOrdenadas) {
        if (capasObstaculos.count(nombreCapa) < 0) continue;
        for (auto& obstaculo: capasObstaculos[nombreCapa])
            obstruibles.push_back(&obstaculo);
    }
    // TODO: no sé si es necesario
    this->filas = mapaParser.getFilas();
    this->columnas = mapaParser.getColumnas();
    this->ancho_tile = mapaParser.getAnchoTile();
    this->alto_tile = mapaParser.getAltoTile();
    //obstruibles.push_back(&personaje);
    //obstruibles.push_back(&enemigo);
}

#define RADIO 16.0f
static bool obstruible_cmp(IObstruible* obstruible,  IObstruible* otro) {
    return otro->getY() + otro->getAlto() > obstruible->getY() + 
                                                obstruible->getAlto();
}
void Escena::render() {
    float zoom = ventana->getAncho() / (mapa.getAnchoTile() * RADIO);
    zoom = round(zoom * mapa.getAnchoTile()) / mapa.getAnchoTile();
    camara.centrar(renderer, zoom);

    mapa.render();
    // TODO: se debería acotar a lo visible
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFrente) {
            int id = capa.second[i];
            if (id == 0) continue;
            int x = i % columnas;
            int y = (i - x) / columnas;
            Imagen* tile = conjuntosTiles.getTile(id);
            if (tile == nullptr) continue;
            tile->setPosicion(x * ancho_tile, y * alto_tile);
            tile->render();
        }
    }
    
    std::stable_sort(obstruibles.begin(), obstruibles.end(), obstruible_cmp);

    // TODO: se debería acotar a lo visible
    for (auto& obstruible: obstruibles)
        obstruible->render();
    camara.reiniciar(renderer);
}

void Escena::manejarEvento(const SDL_Event& event) {
    //personaje.manejarEvento(event);
}

void Escena::actualizar(unsigned int delta_t) {
    /*
    int __i = 0;
    int __maximo = 300;

    mapa.actualizar(delta_t);
    enemigo.actualizar(delta_t);
    personaje.actualizar(delta_t);
    // DEBUG
    int direccion = 4 * __i / __maximo;
    if (direccion == 0)
        enemigoModelo.moverArriba();
    else if (direccion == 1)
        enemigoModelo.moverDerecha();
    else if (direccion == 2)
        enemigoModelo.moverAbajo();
    else if (direccion == 3)
        enemigoModelo.moverIzquierda();
    __i++;
    if (__i == __maximo) {
        __i = 0;
    }
    */
}
