#include "Animacion.h"
#include <string>

Animacion::Animacion(Imagen& imagen, mascaras_t mascaras, 
    const std::string& animacion_inicial): imagen(&imagen), mascaras(mascaras) {
    animacion_actual = animacion_inicial;
    SDL_Rect mascara = mascaras[animacion_actual][0];
    this->imagen->setMascara(mascara.x, mascara.y, mascara.w, mascara.h);
    tiempo_hasta_proximo_cuadro = 0;
    tiempo_hasta_proximo_ciclo = 0;
}

void Animacion::setAnimacion(const std::string& animacion) {
    if (animacion == animacion_actual) return;
    animacion_actual = animacion;
    cuadro = 0;
    tiempo_hasta_proximo_cuadro = 0;
    tiempo_hasta_proximo_ciclo = 0;
}

void Animacion::actualizar(unsigned int delta_t) {
    tiempo_hasta_proximo_ciclo -= delta_t;
    if (tiempo_hasta_proximo_ciclo > 0) return;
    if (tiempo_hasta_proximo_cuadro <= 0) {
        SDL_Rect mascara = mascaras[animacion_actual][cuadro];
        imagen->setMascara(mascara.x, mascara.y, mascara.w, mascara.h);
        tiempo_hasta_proximo_cuadro = tiempo_por_cuadro;
        ++cuadro;
        if (cuadro == mascaras[animacion_actual].size()) {
            tiempo_hasta_proximo_ciclo = tiempo_por_ciclo;
            cuadro = 0;
        }
    }
    tiempo_hasta_proximo_cuadro -= delta_t;
}
