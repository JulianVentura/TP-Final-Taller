#include "Reloj.h"

Reloj::Reloj(): comienzo(reloj_t::now()) {}


double Reloj::medir() {
    fin = reloj_t::now();
    std::chrono::duration<double> diferencia = fin - comienzo;
    comienzo = fin;
    return diferencia.count();
}
