#include "Escena.h"
#include "MovibleVista.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "IObstruible.h"

#define FACTOR 1.0f

using json = nlohmann::json;



class Obstaculo: public IObstruible {
public:
    Obstaculo(SDL_Rect& dimension, std::vector<int>& guids, int ancho_tile, int alto_tile);
    void render() override;

private:
    int columna;
    int fila;
    int ultima_columna;
    int ultima_fila;
    std::vector<int>& guids;
};

std::unordered_map<std::string, std::vector<int>> capasFrente;
std::unordered_map<std::string, std::vector<Obstaculo>> capasObstaculos;
std::vector<std::string> capasOrdenadas;
std::vector<std::vector<int>> capasFondo;
std::vector<TileConjunto> conjuntosTiles;

// class MapaParser {
// public:
//     MapaParser(EntornoGrafico& entorno, std::istream& fuente);
// };

// MapaParser::MapaParser(EntornoGrafico& entorno, std::istream& fuente) {
//     json parser;
//     fuente >> parser;
//     for (auto& grupo: parser["layers"]) {
//         if (grupo["type"] == "group" && grupo["name"] == "fondo") {
//             for (auto& capa: grupo["layers"]) {
//                 capasFondo.push_back(capa["data"].get<std::vector<int>>());
//             }
//         } else if (grupo["type"] == "group" && grupo["name"] == "frente") {
//             for (auto& capa: grupo["layers"]) {
//                 if (capa["type"] == "tilelayer") {
//                     capasFrente.insert({capa["name"], capa["data"].get<std::vector<int>>()});
//                     capasOrdenadas.push_back(capa["name"]);
//                 } else if (capa["type"] == "objectgroup") {
//                     std::string nombre(capa["name"]);
//                     std::vector<SDL_Rect> vector;
//                     for (auto& objeto: capa["objects"]) {
//                         SDL_Rect rect = {};
//                         objeto["x"].get_to(rect.x);
//                         objeto["y"].get_to(rect.y);
//                         objeto["width"].get_to(rect.w);
//                         objeto["height"].get_to(rect.h);
//                         vector.push_back(rect);
//                     }
//                     capasObstaculos.insert({nombre, std::move(vector)});
//                 }
//             }
//         }
//     }
    
//     for (auto& tileset: parser["tilesets"]) {
//         std::string ruta;
//         unsigned int columnas;
//         unsigned int primer_id;
//         unsigned int cantidad_tiles;
//         unsigned int ancho_tile;
//         unsigned int alto_tile;
//         std::string color_transparente;

//         tileset["columns"].get_to(columnas);
//         tileset["firstgid"].get_to(primer_id);
//         tileset["image"].get_to(ruta);
//         tileset["tilecount"].get_to(cantidad_tiles);
//         tileset["tileheight"].get_to(alto_tile);
//         tileset["tilewidth"].get_to(ancho_tile);
//         Imagen imagen;
//         if (tileset.count("transparentcolor") > 0) {
//             tileset["transparentcolor"].get_to(color_transparente);
//             SDL_Color color = renderer->colorDesdeHexa(color_transparente);
//             imagen = Imagen(entorno, "assets/" + ruta, &color);
//         } else {
//             imagen = Imagen(entorno, "assets/" + ruta);
//         }

//         conjuntosTiles.push_back(std::move(TileConjunto(std::move(imagen), columnas, primer_id, 
//         cantidad_tiles, ancho_tile, alto_tile)));
//     }
// }

int columnas;
int filas;
int ancho_tile;
int alto_tile;
std::vector<IObstruible*> obstruibles;

Escena::Escena(EntornoGrafico& entorno): personaje(entorno, personajeModelo), 
                            enemigo(entorno, enemigoModelo) /*, mapa(entorno)*/ {
    entorno.agregarRendereable(this);
    camara = Camara(&mapa, ventana, FACTOR);
    camara.setObjetivo(personaje);
    std::ifstream fuente("assets/mapa.json");
    json parser;
    fuente >> parser;
    parser["height"].get_to(filas);
    parser["width"].get_to(columnas);
    parser["tileheight"].get_to(alto_tile);
    parser["tilewidth"].get_to(ancho_tile);

    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "fondo") continue;
        for (auto& capa: grupo["layers"]) {
            capasFondo.push_back(capa["data"].get<std::vector<int>>());
        }
    }
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "frente") continue;
        for (auto& capa: grupo["layers"]) {
            if (capa["type"] == "tilelayer") {
                capasFrente.insert({capa["name"], capa["data"].get<std::vector<int>>()});
                capasOrdenadas.push_back(capa["name"]);
            }
        }
    }
    for (auto& grupo: parser["layers"]) {
        if (grupo["type"] != "group" || grupo["name"] != "frente") continue;
        for (auto& capa: grupo["layers"]) {
            if (capa["type"] != "objectgroup") continue;
            std::string nombre(capa["name"]);
            std::vector<Obstaculo> vector;
            for (auto& objeto: capa["objects"]) {
                SDL_Rect rect = {};
                objeto["x"].get_to(rect.x);
                objeto["y"].get_to(rect.y);
                objeto["width"].get_to(rect.w);
                objeto["height"].get_to(rect.h);
                vector.push_back(std::move(Obstaculo(rect, capasFrente[nombre], ancho_tile, alto_tile)));
            }
            capasObstaculos.insert({nombre, std::move(vector)});
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
    mapa = MapaVista(entorno, conjuntosTiles, capasFondo, columnas, filas, ancho_tile, alto_tile);
    for (const auto& nombreCapa: capasOrdenadas) {
        if (capasObstaculos.count(nombreCapa) < 0) continue;
        for (auto& obstaculo: capasObstaculos[nombreCapa]) {
            obstruibles.push_back(&obstaculo);
        }
    }
    obstruibles.push_back(&personaje);
    obstruibles.push_back(&enemigo);

}


Obstaculo::Obstaculo(SDL_Rect& dimension, std::vector<int>& guids, int ancho_tile, int alto_tile): guids(guids) {
    columna = dimension.x / ancho_tile;
    fila = dimension.y / alto_tile;
    ultima_columna = (dimension.x + dimension.w) / ancho_tile;
    ultima_fila = (dimension.y + dimension.h) / alto_tile;
    this->ancho = dimension.w;
    this->alto = dimension.h;
    this->x = dimension.x;
    this->y = dimension.y;
}

void Obstaculo::render() {
    for (int i = columna; i <= ultima_columna; ++i) {
        for (int j = fila; j <= ultima_fila; ++j) {
            int indice = j * columnas + i;
            unsigned int id = guids[indice];
            Imagen* tile;
            for (auto& conjunto_tile: conjuntosTiles) {
                if (!conjunto_tile.contieneId(id)) continue;
                Imagen* tile = conjunto_tile.imagenPorId(id);
            }
            tile->setPosicion(i * ancho_tile, j * alto_tile);
            tile->render();
        }
    }
}

void Escena::render() {
    camara.centrar(renderer);

    mapa.render();

    // TODO: se debería acotar a lo visible
    for (int i = 0; i < columnas * filas; ++i) {
        for (auto& capa: capasFrente) {
            int id = capa.second[i];
            int x = i % columnas;
            int y = (i - x) / columnas;
            Imagen* tile;
            for (auto& conjunto_tile: conjuntosTiles) {
                if (!conjunto_tile.contieneId(id)) continue;
                tile = conjunto_tile.imagenPorId(id);
            }
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

    camara.reiniciar(renderer);
}

void Escena::manejarEvento(const SDL_Event& event) {
    mapa.manejarEvento(event);
    personaje.manejarEvento(event);
}

int i = 0;
int maximo = 300;

void Escena::actualizar(unsigned int delta_t) {
    mapa.actualizar(delta_t);
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
    }
}
