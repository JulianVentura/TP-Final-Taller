#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "ServidorProxy.h"
#include "IPosicionable.h"

class Personaje: public IPosicionable {
public:
    Personaje(std::string& id, ServidorProxy& servidor);
    void mover(uint32_t direccion);

private:
    std::string id;
    ServidorProxy& servidor;
    std::string color_fondo;
    std::string ruta_imagen;
    std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras;
    friend class MovibleVista;
};

#endif
