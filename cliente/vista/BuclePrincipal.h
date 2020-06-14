#ifndef BUCLEPRINCIPAL_H
#define BUCLEPRINCIPAL_H

#include "Ventana.h"

class BuclePrincipal {
public:
    explicit BuclePrincipal(Ventana& ventana);
    void correr();

private:
    Ventana* ventana;
    unsigned int ultima_actualizacion;
};

#endif
