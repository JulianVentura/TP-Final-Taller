#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "../vista/Ventana.h"
#include "../controlador/GUI_Boton_Controlador.h"

class BuclePrincipal {
public:
    BuclePrincipal(Ventana& ventana) : ventana(&ventana) {}
    void correr();
private:
    Ventana* ventana;
    std::vector<GUI_BotonControlador*> botones;
};

#endif
