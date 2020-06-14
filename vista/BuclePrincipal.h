#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Ventana.h"

class BuclePrincipal {
public:
    BuclePrincipal(Ventana& ventana) : ventana(&ventana) {}
    void correr();
private:
    Ventana* ventana;
};

#endif
