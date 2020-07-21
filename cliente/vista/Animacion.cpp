#include "Animacion.h"
#include "AnimacionCuatroDirecciones.h"
#include "../modelo/parsers/AnimacionParser.h"
#include <string>

#define DELTA_T 40

Animacion::Animacion() {
    reiniciar();
}

void Animacion::setMascara(AnimacionParser* parser, SDL_Rect& mascara, 
                                    std::string& direccion, bool esta_quieto) {
    if (!accion.size()) accion = parser->getEstadoInicial();
    this->direccion = direccion;
    if (esta_quieto) columna = 0;
    int guid = parser->getGuid(accion, direccion, columna, esta_quieto);
    int ancho = parser->getAncho();
    int alto = parser->getAlto();
    int fila = (guid - columna) / parser->getColumnas();
    mascara = { columna * ancho, fila * alto, ancho, alto };
}

void Animacion::setInfo(AnimacionBase* infoAnimacion) {
    if (!infoAnimacion) return;
    this->infoAnimacion = infoAnimacion;
    tiempo_por_ciclo = infoAnimacion->getTiempoPorCiclo();
    tiempo_por_cuadro = infoAnimacion->getTiempoPorCuadro();
    reiniciar();
}
void Animacion::actualizar(unsigned int delta_t) {
    if (!infoAnimacion) return;
    ultimo_delta_t = delta_t;
}

void Animacion::setMascara(SDL_Rect& mascara, int delta_x, int delta_y) {
    if (!infoAnimacion) return;
    infoAnimacion->getMascara(*this, direccion, mascara, delta_x, delta_y);
}

void Animacion::avanzar() {
    if (!infoAnimacion) return;
    if (tiempo_hasta_proximo_ciclo > 0) {
        tiempo_hasta_proximo_ciclo -= ultimo_delta_t;
        return;
    }
    if (tiempo_hasta_proximo_cuadro > 0) {
        tiempo_hasta_proximo_cuadro -= ultimo_delta_t;
        return;
    }
    if (tiempo_hasta_proximo_cuadro <= 0) 
        tiempo_hasta_proximo_cuadro = tiempo_por_cuadro;
    ++columna;
    if (columna >= infoAnimacion->getColumnas(accion, direccion)) {
        tiempo_hasta_proximo_ciclo = tiempo_por_ciclo;
        tiempo_hasta_proximo_cuadro = 0;
        columna = 0;
    }
}

void Animacion::reiniciar() {
    columna = 0;
    tiempo_hasta_proximo_cuadro = 0;
    tiempo_hasta_proximo_ciclo = 0;
}

void Animacion::setAccion(const std::string& accion) {
    if (this->accion == accion) return;
    this->accion = accion;
}

void Animacion::setTiempoPorCiclo(unsigned int tiempo_por_ciclo) {
    this->tiempo_por_ciclo = tiempo_por_ciclo;
}

void Animacion::setTiempoPorCuadro(unsigned int tiempo_por_cuadro) {
    this->tiempo_por_cuadro = tiempo_por_cuadro;
}
