#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Reloj.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"
#include "../modelo/ServidorProxy.h"
#include "../controlador/IInteractivo.h"
#include <vector>

class BuclePrincipal {
private:
    Ventana* ventana;
    GUI_Principal& gui;
    ServidorProxy& servidor;
    bool salir = false;
    void despacharEventos(SDL_Event& event);
    std::vector<IInteractivo *> interactivos;
    std::vector<IRendereable *> rendereables;
    Reloj reloj;

public:
    BuclePrincipal(Ventana& ventana, GUI_Principal& gui, 
                                                    ServidorProxy& servidor);
    void agregarInteractivo(IInteractivo* interactivo);
    void agregarRendereable(IRendereable* rendereable);
    void correr();
};

#endif
