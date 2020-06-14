#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "../vista/Ventana.h"
#include "../controlador/GUI_Boton_Controlador.h"

class BuclePrincipal {
public:
    explicit BuclePrincipal(Ventana& ventana);
    void correr();
	std::vector<GUI_BotonControlador*> botones;

private:
    void despacharEventos(SDL_Event& event);
    Ventana* ventana;
    unsigned int ultima_actualizacion;
    bool salir = false;
};

#endif