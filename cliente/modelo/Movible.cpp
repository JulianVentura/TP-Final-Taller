#include "Movible.h"
#include <vector>
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define RUTA_INFO "assets/cliente.json"
#include <fstream>

Movible::Movible(std::string& id_movible): id_movible(id_movible) {
    std::ifstream fuente(RUTA_INFO);
    json j;
    fuente >> j;
    std::string raiz;
    j["raiz"].get_to(raiz);
    std::string ruta;
    j["personajes"][id_movible]["archivo"].get_to(ruta);
    j["personajes"][id_movible]["color-fondo"].get_to(color_fondo);

    this->ruta_imagen = raiz + ruta;

    for (auto& mascara: j["personajes"][id_movible]["mascaras"].items()) {
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
