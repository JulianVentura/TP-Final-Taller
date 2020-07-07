#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Reloj.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"
#include "../modelo/ServidorProxy.h"
#include "../controlador/IInteractivo.h"
#include <vector>
#include <unordered_map>

#define FPS 60
#define SEG_A_MILLI 1000
#define MILLIS_POR_FRAME SEG_A_MILLI / FPS

class BuclePrincipal {
private:
    Ventana* ventana;
    void despacharEventos(SDL_Event& evento);
    std::unordered_map<Uint32, std::vector<IInteractivo *>> interactivos;
    Reloj reloj;
    bool salir = false;

public:
    BuclePrincipal(Ventana& ventana);
    void agregarInteractivo(Uint32 tipo_evento, IInteractivo* interactivo);
    void correr();
};

#endif
