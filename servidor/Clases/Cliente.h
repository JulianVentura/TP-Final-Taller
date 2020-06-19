#ifndef __CLIENTE_H__
#define __CLIENTE_H__
#include "Personaje.h"
class Cliente{
    private:
    Personaje personaje;
    std::string id;
    public:
    Cliente(std::string &id);
    Cliente(Cliente &&otro) = delete;
    Cliente(Cliente &otro) = delete;
    Cliente& operator=(Cliente &&otro) = delete;
    Cliente& operator=(Cliente &otro) = delete;
    void enviarPosiciones(std::string &posiciones);
    std::string obtenerId();
    Personaje* obtenerPersonaje();
};

#endif
