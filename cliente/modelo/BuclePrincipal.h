#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "../vista/Ventana.h"
#include "../controlador/GUI_Boton_Controlador.h"

class BuclePrincipal {
public:
	std::vector<GUI_BotonControlador*> botones;
    BuclePrincipal(Ventana& ventana) : ventana(&ventana) {}
    void correr();
private:
    Ventana* ventana;
    
};

#endif
