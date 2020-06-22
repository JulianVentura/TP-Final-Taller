#include "MapaVista.h"
#include <iostream>
#include <string>
#include "TileConjunto.h"
// TODO: se está pasando todo por copia
MapaVista::MapaVista(EntornoGrafico& entorno, 
std::vector<TileConjunto> conjuntosTiles,
std::vector<std::vector<int>> capasFondo, int columnas, int filas, int ancho_tile, int alto_tile) : conjuntosTiles(conjuntosTiles),
capasFondo(capasFondo), columnas(columnas), filas(filas), ancho_tile(ancho_tile), alto_tile(alto_tile) {
    entorno.agregarRendereable(this);

    // std::ifstream data("assets/mapa.json");
    // json parser;
    // data >> parser;
    // for (auto& grupo: parser["layers"]) {
    //     if (grupo["type"] == "group" && grupo["name"] == "fondo") {
    //         for (auto& capa: grupo["layers"]) {
    //             capasFondo.push_back(capa["data"].get<std::vector<int>>());
    //         }
    //     } else if (grupo["type"] == "group" && grupo["name"] == "frente") {
    //         for (auto& capa: grupo["layers"]) {
    //             if (capa["type"] == "tilelayer") {
    //                 capasFrente.insert({capa["name"], capa["data"].get<std::vector<int>>()});
    //                 capasOrdenadas.push_back(capa["name"]);
    //             } else if (capa["type"] == "objectgroup") {
    //                 std::string nombre(capa["name"]);
    //                 std::vector<SDL_Rect> vector;
    //                 for (auto& objeto: capa["objects"]) {
    //                     SDL_Rect rect = {};
    //                     objeto["x"].get_to(rect.x);
    //                     objeto["y"].get_to(rect.y);
    //                     objeto["width"].get_to(rect.w);
    //                     objeto["height"].get_to(rect.h);
    //                     vector.push_back(rect);
    //                 }
    //                 capasObstaculos.insert({nombre, std::move(vector)});
    //             }
    //         }
    //     }
    // }
    
    // for (auto& tileset: parser["tilesets"]) {
    //     std::string ruta;
    //     unsigned int columnas;
    //     unsigned int primer_id;
    //     unsigned int cantidad_tiles;
    //     unsigned int ancho_tile;
    //     unsigned int alto_tile;
    //     std::string color_transparente;

    //     tileset["columns"].get_to(columnas);
    //     tileset["firstgid"].get_to(primer_id);
    //     tileset["image"].get_to(ruta);
    //     tileset["tilecount"].get_to(cantidad_tiles);
    //     tileset["tileheight"].get_to(alto_tile);
    //     tileset["tilewidth"].get_to(ancho_tile);
    //     Imagen imagen;
    //     if (tileset.count("transparentcolor") > 0) {
    //         tileset["transparentcolor"].get_to(color_transparente);
    //         SDL_Color color = renderer->colorDesdeHexa(color_transparente);
    //         imagen = Imagen(entorno, "assets/" + ruta, &color);
    //     } else {
    //         imagen = Imagen(entorno, "assets/" + ruta);
    //     }

    //     conjuntosTiles.push_back(std::move(TileConjunto(std::move(imagen), columnas, primer_id, 
    //     cantidad_tiles, ancho_tile, alto_tile)));
    // }

    this->ancho = columnas * ancho_tile;
    this->alto = filas * alto_tile;
}

void MapaVista::actualizar(unsigned int delta_t) {
}

void MapaVista::render() {
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFondo) {
            int id = capa[i];
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
    }

    // for (unsigned int i = 0; i < columnas * filas; ++i) {
    //     for (auto& capa: capasFrente) {
    //         unsigned int id = capa.second[i];
    //         for (auto& conjunto_tile: conjuntosTiles) {
    //             if (!conjunto_tile.contieneId(id)) continue;
    //             Imagen* tile = conjunto_tile.imagenPorId(id);
    //             int x = i % columnas;
    //             int y = (i - x) / columnas;
    //             tile->setPosicion(x * ancho_tile, y * alto_tile);
    //             tile->render();
    //        }
    //     }
    // }
    // for (const auto& nombreCapa: capasOrdenadas) {
    //     if (capasObstaculos.count(nombreCapa) < 0) continue;
    //     for (auto& obstaculo: capasObstaculos[nombreCapa]) {
    //         int columna = obstaculo.x / (int)ancho_tile;
    //         int fila = obstaculo.y / (int)alto_tile;
    //         int ultima_columna = (obstaculo.x + obstaculo.w) / (int)ancho_tile;
    //         int ultima_fila = (obstaculo.y + obstaculo.h) / (int)alto_tile;
    //         renderer->setColor(51, 0, 51);
            
    //         for (int i = columna; i <= ultima_columna; ++i) {
    //             for (int j = fila; j <= ultima_fila; ++j) {
    //                 int indice = j * columnas + i;
    //                 unsigned int id = capasFrente[nombreCapa][indice];
    //                 if (nombreCapa == "arboles-1")
    //                     renderer->rectSolido(i * ancho_tile, j * alto_tile, 10, 10);
    //                 for (auto& conjunto_tile: conjuntosTiles) {
    //                     if (!conjunto_tile.contieneId(id)) continue;
    //                     Imagen* tile = conjunto_tile.imagenPorId(id);
    //                     tile->setPosicion(i * ancho_tile, j * alto_tile);
    //                     tile->render();
    //                }
    //             }
    //         }
    //         renderer->setColor(51, 0, 51);
    //         renderer->rect(obstaculo.x, obstaculo.y, obstaculo.w, obstaculo.h);
    //         renderer->texto(nombreCapa, obstaculo.x, obstaculo.y);
    //     }
    // }
}

void MapaVista::manejarEvento(const SDL_Event& event) {
}
