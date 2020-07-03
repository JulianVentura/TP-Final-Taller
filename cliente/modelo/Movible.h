#ifndef MOVIBLE_H
#define MOVIBLE_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "ServidorProxy.h"
#include "IPosicionable.h"

class Movible: public IPosicionable {
public:
    Movible(std::string& id_personaje, ServidorProxy& servidor);
    void mover(uint32_t direccion);

private:
    std::string id_movible;
    ServidorProxy& servidor;
    std::string color_fondo;
    std::string ruta_imagen;
    std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras;
    friend class MovibleVista;
};

#endif
