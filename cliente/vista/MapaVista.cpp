#include "MapaVista.h"
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class TileConjunto {
public:
    TileConjunto(Imagen imagen, unsigned int columnas, unsigned int primer_id, 
        unsigned int cantidad_tiles, unsigned int ancho_tile,
        unsigned int alto_tile);
    bool contieneId(unsigned int id);
    Imagen* imagenPorId(unsigned int id);

private:
    Imagen imagen;
    unsigned int columnas;
    unsigned int primer_id;
    unsigned int cantidad_tiles;
    unsigned int ancho_tile;
    unsigned int alto_tile;
};

TileConjunto::TileConjunto(Imagen imagen, unsigned int columnas, unsigned int 
        primer_id, unsigned int cantidad_tiles, unsigned int ancho_tile,
        unsigned int alto_tile): 
        imagen(imagen), columnas(columnas), primer_id(primer_id), 
        cantidad_tiles(cantidad_tiles), ancho_tile(ancho_tile), 
        alto_tile(ancho_tile) {}

bool TileConjunto::contieneId(unsigned int id) {
    return primer_id <= id && (primer_id + cantidad_tiles) > id;
}

Imagen* TileConjunto::imagenPorId(unsigned int id) {
    if (!contieneId(id)) return NULL;
    unsigned int id_relativo = id - primer_id;
    int x = id_relativo % columnas;
    int y = (id_relativo - x) / columnas;
    imagen.setMascara(x * ancho_tile, y * alto_tile, ancho_tile, alto_tile);
    return &imagen;
}
std::vector<std::vector<int>> capasFondo;
std::vector<std::vector<int>> capasFrente;
std::vector<TileConjunto> conjuntosTiles;

MapaVista::MapaVista(EntornoGrafico& entorno) {
    entorno.agregarRendereable(this);

    std::ifstream data("assets/mapa2.json");
    json parser;
    data >> parser;
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] == "group" && grupo["name"] == "fondo") {
            for (auto& capa: grupo["layers"]) {
                capasFondo.push_back(capa["data"].get<std::vector<int>>());
            }
        } else if (grupo["type"] == "group" && grupo["name"] == "frente") {
            for (auto& capa: grupo["layers"]) {
                if (capa["type"] != "tilelayer") continue;
                capasFrente.push_back(capa["data"].get<std::vector<int>>());
            }
        }
    }
    
    for (auto& tileset: parser["tilesets"]) {
        std::string ruta;
        unsigned int columnas;
        unsigned int primer_id;
        unsigned int cantidad_tiles;
        unsigned int ancho_tile;
        unsigned int alto_tile;
        std::string color_transparente;

        tileset["columns"].get_to(columnas);
        tileset["firstgid"].get_to(primer_id);
        tileset["image"].get_to(ruta);
        tileset["tilecount"].get_to(cantidad_tiles);
        tileset["tileheight"].get_to(alto_tile);
        tileset["tilewidth"].get_to(ancho_tile);
        Imagen imagen;
        if (tileset.count("transparentcolor") > 0) {
            tileset["transparentcolor"].get_to(color_transparente);
            SDL_Color color = renderer->colorDesdeHexa(color_transparente);
            imagen = Imagen(entorno, "assets/" + ruta, &color);
        } else {
            imagen = Imagen(entorno, "assets/" + ruta);
        }

        conjuntosTiles.push_back(std::move(TileConjunto(std::move(imagen), columnas, primer_id, 
        cantidad_tiles, ancho_tile, alto_tile)));
    }
    parser["height"].get_to(filas);
    parser["width"].get_to(columnas);
    parser["tileheight"].get_to(alto_tile);
    parser["tilewidth"].get_to(ancho_tile);

    ancho = columnas * ancho_tile;
    alto = filas * alto_tile;
}

void MapaVista::actualizar(unsigned int delta_t) {
}

void MapaVista::render() {
    for (unsigned int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFondo) {
            unsigned int id = capa[i];
            for (auto& conjunto_tile: conjuntosTiles) {
                if (id == 0) break;
                if (!conjunto_tile.contieneId(id)) continue;
                Imagen* tile = conjunto_tile.imagenPorId(id);
                int x = i % columnas;
                int y = (i - x) / columnas;
                tile->setPosicion(x * ancho_tile, y * alto_tile);
                tile->render();
           }
        }
        for (auto& capa: capasFrente) {
            unsigned int id = capa[i];
            for (auto& conjunto_tile: conjuntosTiles) {
                if (!conjunto_tile.contieneId(id)) continue;
                Imagen* tile = conjunto_tile.imagenPorId(id);
                int x = i % columnas;
                int y = (i - x) / columnas;
                tile->setPosicion(x * ancho_tile, y * alto_tile);
                tile->render();
           }
        }
    }
}

void MapaVista::manejarEvento(const SDL_Event& event) {
}
