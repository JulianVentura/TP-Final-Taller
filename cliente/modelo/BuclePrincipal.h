#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"

class BuclePrincipal {
private:
    Ventana* ventana;
    GUI_Principal& gui;
    unsigned int ultima_actualizacion;
    bool salir = false;
    void despacharEventos(SDL_Event& event);

public:
    explicit BuclePrincipal(Ventana& ventana, GUI_Principal& gui);
    void correr();
};

#endif
