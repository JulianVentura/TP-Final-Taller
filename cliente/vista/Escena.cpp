#include "Escena.h"
#include "MovibleVista.h"
#include <fstream>
#include <algorithm>
#include "IObstruible.h"
#include "MapaParser.h"
#include "LibreriaConjuntoTileParser.h"
#include "LibreriaConjuntoTiles.h"
#include "ObstaculoParser.h"
#include "CapasParser.h"

#define FACTOR 1.0f

// TODO: provisorio
// std::vector<IObstruible*> obstruibles;

Escena::Escena(EntornoGrafico& entorno): personaje(entorno, personajeModelo), 
                            enemigo(entorno, enemigoModelo) /*, mapa(entorno)*/ {
    exit(0);
    // entorno.agregarRendereable(this);
/*
    camara.setObjetivo(personaje);
    std::ifstream fuente("assets/mapa.json");
    
    CapasParser capasParser(fuente);
    this->capasFrente = std::move(capasParser.getCapas());
    this->capasOrdenadas = std::move(capasParser.getCapasOrdenadas());
    fuente = std::ifstream("assets/mapa.json");
    
    LibreriaConjuntoTileParser libreriaConjuntoTileParser(fuente);
    conjuntosTiles = LibreriaConjuntoTiles(entorno, libreriaConjuntoTileParser);
    Imagen* im = conjuntosTiles.getTile(30);
    printf("%d\n", im->getAlto());
    // exit(0);
    fuente = std::ifstream("assets/mapa.json");

    ObstaculoParser obstaculoParser(fuente, capasFrente, conjuntosTiles);
    this->capasObstaculos = std::move(obstaculoParser.getCapasObstaculos());
    
    fuente = std::ifstream("assets/mapa.json");
    MapaParser mapaParser(fuente);
    // mapa = MapaVista(entorno, mapaParser, conjuntosTiles);

    for (const auto& nombreCapa: capasOrdenadas) {
        if (capasObstaculos.count(nombreCapa) < 0) continue;
        for (auto& obstaculo: capasObstaculos[nombreCapa]) {
            obstruibles.push_back(&obstaculo);
        }
    }

    // TODO: no sé si es necesario
    filas = mapaParser.getFilas();
    columnas = mapaParser.getColumnas();
    ancho_tile = mapaParser.getAnchoTile();
    alto_tile = mapaParser.getAltoTile();

    obstruibles.push_back(&personaje);
    obstruibles.push_back(&enemigo);
    // camara = Camara(&mapa, ventana, FACTOR);

    */
}

void Escena::render() {
    // camara.centrar(renderer);

    // mapa.render();
/*
    // TODO: se debería acotar a lo visible
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFrente) {
            int id = capa.second[i];
            int x = i % columnas;
            int y = (i - x) / columnas;
            Imagen* tile = conjuntosTiles.getTile(id);
            tile->setPosicion(x * ancho_tile, y * alto_tile);
            tile->render();
        }
    }
    
    std::sort(obstruibles.begin(), obstruibles.end(), [](IObstruible* obstruible,  IObstruible* otro) {
        return otro->getY() + otro->getAlto() > obstruible->getY() + obstruible->getAlto();
    });

    // TODO: se debería acotar a lo visible
    for (auto& obstruible: obstruibles) {
        obstruible->render();
    }

    // camara.reiniciar(renderer);
    */
}

void Escena::manejarEvento(const SDL_Event& event) {
    // mapa.manejarEvento(event);
    // personaje.manejarEvento(event);
}

// int i = 0;
// int maximo = 300;

void Escena::actualizar(unsigned int delta_t) {
    // mapa.actualizar(delta_t);
    /*
    enemigo.actualizar(delta_t);
    personaje.actualizar(delta_t);
    
    // DEBUG
    int direccion = 4 * i / maximo;
    if (direccion == 0)
        enemigoModelo.moverAbajo();
    else if (direccion == 1)
        enemigoModelo.moverIzquierda();
    else if (direccion == 2)
        enemigoModelo.moverArriba();
    else if (direccion == 3)
        enemigoModelo.moverDerecha();

    i++;
    if (i == maximo) {
        i = 0;
    }*/
}
