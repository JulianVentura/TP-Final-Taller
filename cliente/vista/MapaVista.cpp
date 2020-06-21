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
/**
 * id = some_id
 * for tileset in tilesets:
 *      if (!tileset.contiene(id)): continue
 *      relative_id = id - tileset.first_id
 *      imagen = tileset.imagen
 *      x = relative_id % tileset.ancho
 *      y = (relative_id - x) / tileset.ancho
 *      imagen.setMascara(x * 32, y * 32 ,32, 32)
 */

Imagen* TileConjunto::imagenPorId(unsigned int id) {
    if (!contieneId(id)) return NULL;
    unsigned int id_relativo = id - primer_id;
    int x = id_relativo % columnas;
    int y = (id_relativo - x) / columnas;
    // imagen.setMascara(x * ancho_tile, y * alto_tile, ancho_tile, alto_tile);
    imagen.setMascara(x * 32, y * 32, 32, 32);
    imagen.setAncho(32);
    imagen.setAlto(32);
    // printf("%d\n", imagen.getAlto());
    
    return &imagen;
}
std::vector<std::vector<int>> capas;
std::vector<TileConjunto> conjuntosTiles;

MapaVista::MapaVista(EntornoGrafico& entorno) {
    entorno.agregarRendereable(this);

    std::ifstream data("assets/mapa.json");
    json parser;
    data >> parser;
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] == "group" && grupo["name"] == "fondo") {
            for (auto& capa: grupo["layers"]) {
                capas.push_back(capa["data"].get<std::vector<int>>());
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

    // const std::string ruta_azul("assets/tile_azul.png");
    // const std::string ruta_verde("assets/tile_verde.png");

    // imagen_tile_azul = Imagen(entorno, ruta_azul);
    // imagen_tile_verde = Imagen(entorno, ruta_verde);

    // for (int i = 0; i < COLUMNAS; ++i) {
    //     for (int j = 0; j < FILAS; ++j) {
    //         int x = i * ANCHO_TILE;
    //         int y = j * ANCHO_TILE;
    //         if (terreno[i][j])
    //             tiles.push_back(std::move(Tile(entorno, &imagen_tile_azul, x, y)));
    //         else 
    //             tiles.push_back(std::move(Tile(entorno, &imagen_tile_verde, x, y)));
    //     }
    // }

    ancho = columnas * ancho_tile;
    alto = filas * alto_tile;

}

void MapaVista::actualizar(unsigned int delta_t) {
    // for (auto& tile: tiles) 
        // tile.actualizar(delta_t);
}
// ancho
// alto
// ancho tile
// alto tile

// layers
//      nxm con ids
/**
 * for i in range(alto * ancho): // se podría acotar
 *      for layer in layers: // se podría acotar
 *          id = layer[row + col]
 *          if (id == 0): continue
 *          imagenPorId(id)->render()
 */ 
/**
 * id = some_id
 * for tileset in tilesets:
 *      if (!tileset.contiene(id)): continue
 *      relative_id = id - tileset.first_id
 *      imagen = tileset.imagen
 *      x = relative_id % tileset.ancho
 *      y = (relative_id - x) / tileset.ancho
 *      imagen.setMascara(x * 32, y * 32 ,32, 32)
 */
// tileset
//      para cada id, tiene una
//      imagen asociada y una región de esa imagen
void MapaVista::render() {
    for (unsigned int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capas) {
            unsigned int id = capa[i];
            for (auto& conjunto_tile: conjuntosTiles) {
                if (!conjunto_tile.contieneId(id)) continue;
                Imagen* tile = conjunto_tile.imagenPorId(id);
                int x = i % columnas;
                int y = (i - x) / columnas;
                tile->setPosicion(x, y);
                tile->render();
           }
        }
    }
    

    // for (auto& tile: tiles)
        // tile.render();
    // imagen_tile_azul.render();
}   

void MapaVista::manejarEvento(const SDL_Event& event) {
}
