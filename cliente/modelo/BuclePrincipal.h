#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Reloj.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"
#include "../modelo/ServidorProxy.h"
#include "../controlador/IInteractivo.h"
#include <vector>
#include <unordered_map>

#define FPS 60.0f
#define SEG_A_MILLI 1000.0f
#define MILLIS_POR_FRAME SEG_A_MILLI / FPS

/*
*	Clase que encapsula un gameloop, desencola eventos de SDL y lo envía
*	a los interactivos que hayan sido agregados.
*/

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
    // Inicia el procesamiento de los eventos de SDL encolados
    void correr();
};

#endif
