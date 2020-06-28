#ifndef __CLIENTE_H__
#define __CLIENTE_H__
#include "Personaje.h"
#include "Sala.h"
#include "PosicionEncapsulada.h"

class Cliente{
    private:
    Personaje personaje;
    std::string id;
    public:
    Cliente(std::string id, std::string nombreMapa, Sala &sala);
    Cliente(Cliente &&otro) = delete;
    Cliente(Cliente &otro) = delete;
    Cliente& operator=(Cliente &&otro) = delete;
    Cliente& operator=(Cliente &otro) = delete;
    void enviarPosiciones(std::vector<struct PosicionEncapsulada> &posiciones);
    std::string obtenerId();
    Personaje* obtenerPersonaje();
};

#endif
