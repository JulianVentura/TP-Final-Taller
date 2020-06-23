#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Reloj.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"

class BuclePrincipal {
private:
    Ventana* ventana;
    GUI_Principal& gui;
    bool salir = false;
    void despacharEventos(SDL_Event& event);
    Reloj reloj;

public:
    explicit BuclePrincipal(Ventana& ventana, GUI_Principal& gui);
    void correr();
};

#endif
