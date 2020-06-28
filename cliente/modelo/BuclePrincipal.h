#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Reloj.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"
#include "../modelo/ServidorProxy.h"
#include "../controlador/Teclas.h"

class BuclePrincipal {
private:
    Ventana* ventana;
    GUI_Principal& gui;
    ServidorProxy& servidor;
    Teclas teclas;
    bool salir = false;
    void despacharEventos(SDL_Event& event);
    Reloj reloj;

public:
    explicit BuclePrincipal(Ventana& ventana, GUI_Principal& gui,
    	ServidorProxy& servidor);
    void correr();
};

#endif
