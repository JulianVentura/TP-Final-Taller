#include "Personaje.h"
#include <vector>
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define RUTA_INFO "assets/cliente.json"
#include <fstream>

Personaje::Personaje(std::string& id, ServidorProxy& servidor): id(id), 
        servidor(servidor) {
    std::ifstream fuente(RUTA_INFO);
    json parser;
    fuente >> parser;
    std::string raiz;
    parser["raiz"].get_to(raiz);
    std::string ruta;
    parser["personajes"][id.c_str()]["archivo"].get_to(ruta);
    parser["personajes"][id.c_str()]["color-fondo"].get_to(this->color_fondo);

    this->ruta_imagen = raiz + ruta;

    for (auto& mascara: parser["personajes"][id.c_str()]["mascaras"].items()) {
        std::string llave(mascara.key());
        std::vector<SDL_Rect> vector;
        for (auto& cuadro: mascara.value()) {
            SDL_Rect rect = {};
            cuadro["x"].get_to(rect.x);
            cuadro["y"].get_to(rect.y);
            cuadro["w"].get_to(rect.w);
            cuadro["h"].get_to(rect.h);
            vector.push_back(std::move(rect));
        }
        mascaras.insert({std::move(llave), std::move(vector)});
    }
}

void Personaje::mover(uint32_t direccion) {
    servidor.enviarMovimiento(direccion);
}
