#include "Animacion.h"
#include <string>

Animacion::Animacion(EntidadParser& parser, const std::string& animacion_inicial):
        parser(parser), tipo(animacion_inicial) {
    tiempo_hasta_proximo_cuadro = 0;
    tiempo_hasta_proximo_ciclo = 0;
}

void Animacion::setMascara(SDL_Rect& mascara) {
    if (tiempo_hasta_proximo_ciclo > 0) return;
    if (tiempo_hasta_proximo_cuadro > 0) return;
    if (esta_quieto) columna = 0;
    int guid = parser.getGuid(tipo, accion, direccion, columna, esta_quieto);
    int ancho = parser.getAncho();
    int alto = parser.getAlto();
    int fila = (guid - columna) / parser.getAnimacionCantidadTipo(tipo);
    mascara = { columna * ancho, fila * alto, ancho, alto };
}

void Animacion::avanzar() {
    if (tiempo_hasta_proximo_cuadro <= 0) 
        tiempo_hasta_proximo_cuadro = tiempo_por_cuadro;
    if (tiempo_hasta_proximo_ciclo > 0) return;
    tiempo_hasta_proximo_cuadro -= ultimo_delta_t;
    ++columna;
    if (columna == parser.getAnimacionCantidad(tipo, accion, direccion)) {
        tiempo_hasta_proximo_ciclo = tiempo_por_ciclo;
        columna = 0;
    }
}

void Animacion::reiniciar() {
    columna = 0;
    tiempo_hasta_proximo_cuadro = 0;
    tiempo_hasta_proximo_ciclo = 0;
}

void Animacion::setAnimacion(const std::string& animacion) {
    if (animacion == tipo) return;
    tipo = animacion;
    reiniciar();
}

void Animacion::setDireccion(const std::string& direccion) {
    if (this->direccion == direccion) return;
    this->direccion = direccion;
    reiniciar();
}

void Animacion::setAccion(const std::string& accion) {
    if (this->accion == accion) return;
    this->accion = accion;
    reiniciar();
}

void Animacion::actualizar(unsigned int delta_t) {
    tiempo_hasta_proximo_ciclo -= delta_t;
    ultimo_delta_t = delta_t;
}
