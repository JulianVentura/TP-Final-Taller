#ifndef MOVIBLE_H
#define MOVIBLE_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "IPosicionable.h"

class Movible: public IPosicionable {
public:
    Movible(std::string& id_personaje);

private:
    std::string id_movible;
    std::string color_fondo;
    std::string ruta_imagen;
    std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras;
    friend class MovibleVista;
};

#endif
