#include "MovibleVista.h"

#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"

#include <SDL2/SDL_timer.h>
#include <vector>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define RUTA_INFO "assets/cliente.json"
#include <fstream>

MovibleVista::MovibleVista(EntornoGrafico& entorno, Personaje& modelo, std::string& id)
        : personajeModelo(modelo) {
    entorno.agregarRendereable(this);

    // TODO: provisorio
    std::ifstream fuente(RUTA_INFO);
    json parser;
    fuente >> parser;
    std::string raiz;
    parser["raiz"].get_to(raiz);
    std::string ruta;
    std::string color_fondo;

    parser["personajes"][id.c_str()]["archivo"].get_to(ruta);
    parser["personajes"][id.c_str()]["color-fondo"].get_to(color_fondo);

    SDL_Color color = renderer->colorDesdeHexa(color_fondo);
    imagen = Imagen(entorno, raiz + ruta, &color);
    std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras;

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


    // TODO: Esto después se cambiaría
    personajeModelo.x = 935;
    personajeModelo.y = 1851;

    this->x = personajeModelo.x;
    this->y = personajeModelo.y;
    animacion = AnimacionEnteDireccionable(imagen, std::move(mascaras), 
                                                        std::string(ABAJO));
    ultimo_estado = ABAJO;
    this->ancho = imagen.getAncho();
    this->alto = imagen.getAlto();
}

void MovibleVista::actualizar(unsigned int delta_t) {
    int ultimo_x = this->x;
    int ultimo_y = this->y;
    personajeModelo.actualizar();
    this->x = personajeModelo.x;
    this->y = personajeModelo.y;
    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    animacion.actualizarEstado(delta_t, delta_x, delta_y);
    imagen.setPosicion(x, y);
}

void MovibleVista::render() {
    imagen.render();
}
