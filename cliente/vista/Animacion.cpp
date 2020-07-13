#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"
#include <string>
#define DELTA_T 25
Animacion::Animacion(EntidadParser& parser, const std::string& tipo):
        parser(parser), tipo(tipo) {
    direccion = ANIMACION_ABAJO;
    reiniciar();
}

void Animacion::setMascara(SDL_Rect& mascara) {
    if (tiempo_hasta_proximo_ciclo > 0) return;
    if (tiempo_hasta_proximo_cuadro > 0) return;
    if (esta_quieto) columna = 0;
    int guid = parser.getGuid(tipo, accion, direccion, columna, esta_quieto);
    int ancho = parser.getAncho(tipo);
    int alto = parser.getAlto(tipo);
    int fila = (guid - columna) / parser.getAnimacionCantidadTipo(tipo);
    mascara = { columna * ancho, fila * alto, ancho, alto };
}

void Animacion::avanzar() {
    if (tiempo_hasta_proximo_cuadro <= 0) 
        tiempo_hasta_proximo_cuadro = tiempo_por_cuadro;
    if (tiempo_hasta_proximo_ciclo > 0) return;
    tiempo_hasta_proximo_cuadro -= ultimo_delta_t;
    ++columna;
    columna %= parser.getAnimacionCantidad(tipo, accion, direccion);
    if (columna == parser.getAnimacionCantidad(tipo, accion, direccion)) 
        tiempo_hasta_proximo_ciclo = tiempo_por_ciclo;
}

void Animacion::reiniciar() {
    columna = 0;
    tiempo_hasta_proximo_cuadro = 0;
    tiempo_hasta_proximo_ciclo = 0;
}

void Animacion::setAnimacion(const std::string& tipo) {
    if (this->tipo == tipo) return;
    this->tipo = tipo;
    reiniciar();
}

void Animacion::setDireccion(const std::string& direccion) {
    if (this->direccion == direccion) return;
    this->direccion = direccion;
    // reiniciar();
}

void Animacion::setAccion(const std::string& accion) {
    if (this->accion == accion) return;
    this->accion = accion;
    // reiniciar();
}

void Animacion::actualizar(unsigned int delta_t) {
    tiempo_hasta_proximo_ciclo -= delta_t;
    ultimo_delta_t = DELTA_T;
}


void Animacion::setTiempoPorCiclo(unsigned int tiempo_por_ciclo) {
    this->tiempo_por_ciclo = tiempo_por_ciclo;
}

void Animacion::setTiempoPorCuadro(unsigned int tiempo_por_cuadro) {
    this->tiempo_por_cuadro = tiempo_por_cuadro;
}
