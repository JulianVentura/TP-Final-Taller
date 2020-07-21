#include "EntidadVista.h"

#include "Animacion.h"
#include "AnimacionCuatroDirecciones.h"
#include "Colores.h"
#include "Camara.h"

#include <SDL2/SDL_rect.h>
#include <mutex>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

#include "EntornoMusical.h"

#define RADIO_SONIDO 15000

EntidadVista::EntidadVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser): 
       entorno(entorno), modelo(modelo), parser(parser) {
    entorno.agregarRendereable(this);
    x = modelo->getX();
    y = modelo->getY();
    ultimo_estado = ANIMACION_BASE;
    esta_apariencia = false;
    reprodujo_sonido = false;
}

void EntidadVista::reproducirSonido(IPosicionable* foco) {
    if (reprodujo_sonido || !foco) return;
    if (std::pow(modelo->getX() - foco->getX(), 2) + 
        std::pow (modelo->getY() - foco->getY(), 2) > RADIO_SONIDO) return;
    std::string id;
    if (estado_anterior.size()){
        id = apariencia.estado + "-" + estado_anterior;
        estado_anterior = "";
    } else {
        id = apariencia.tipo;
    }
    EntornoMusical::obtenerInstancia()->reproducirSonido(id);
    reprodujo_sonido = true;
}

void EntidadVista::actualizar(unsigned int delta_t) {
    if (!esta_apariencia || !modelo || !modelo->esta_actualizado()) return;
    int ultimo_x = x;
    int ultimo_y = y;
    x = modelo->getX();
    y = modelo->getY();
    modelo->consumirActualizacion();
    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    animacion.actualizar(delta_t);
    animacion.setMascara(mascara, delta_x, delta_y);
    animacion.avanzar();
}

void EntidadVista::render() {
    if (!esta_apariencia) return;
    std::unordered_map<std::string, Imagen*> equipables(std::move(parser.getEquipables(apariencia)));
    sprite.setMascara(mascara);
    sprite.setDimension(getX() + ancho / 2, getY() + alto, mascara.w, mascara.h);
    sprite.render(parser, equipables);
}

void EntidadVista::actualizarApariencia(DatosApariencia& apariencia) {
    if (this->apariencia == apariencia) return;
    sprite.actualizar(parser, apariencia);
    if (!estado_anterior.size()) {
        estado_anterior = this->apariencia.estado;
        reprodujo_sonido = estado_anterior != apariencia.estado;
    }
    this->apariencia = apariencia;
    ancho = parser.getAnchoReal(apariencia);
    alto = parser.getAltoReal(apariencia);
    infoAnimacion = sprite.getInfoAnimacion();
    animacion.setInfo(infoAnimacion);
    esta_apariencia = infoAnimacion != nullptr;
}

bool EntidadVista::contienePunto(int x, int y) {
    SDL_Point punto = { x, y };
    SDL_Rect rect = { getX(), getY(), ancho, alto};
    return SDL_PointInRect(&punto, &rect);
}