#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"
#include "../modelo/ServidorProxy.h"

class BuclePrincipal {
private:
    Ventana* ventana;
    GUI_Principal& gui;
    ServidorProxy& servidor;
    unsigned int ultima_actualizacion;
    bool salir = false;
    void despacharEventos(SDL_Event& event);

public:
    explicit BuclePrincipal(Ventana& ventana, GUI_Principal& gui,
    	ServidorProxy& servidor);
    void correr();
};

#endif
