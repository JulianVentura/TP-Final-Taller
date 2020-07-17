#include "EntidadVista.h"

#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"
#include "Colores.h"
#include "Camara.h"

#include <SDL2/SDL_rect.h>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

const std::vector<std::string> EntidadVista::ordenDeImagenes = {
    "cuerpo",
    "ojos",
    "cicatrices",
    "nariz",
    "orejas",
    "facial",
    "pies",
    "piernas",
    "torso",
    "cinto",
    "pelo",
    "cabeza",
    "arma",
    "escudo"
};

EntidadVista::EntidadVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser): 
       modelo(modelo), parser(parser), animacion_local(parser, apariencia.tipo), 
        animacion(parser, apariencia.tipo) {
    entorno.agregarRendereable(this);
    x = modelo->getX();
    y = modelo->getY();
    ultimo_estado = ANIMACION_BASE;
    esta_apariencia = false;
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
    animacion_local.actualizarEstado(delta_t, delta_x, delta_y);
    animacion_local.setMascara(mascara);
    animacion_local.avanzar();
}

void renderImagen(Imagen* imagen, SDL_Rect& mascara, int x, int y, int ancho, int alto) {
    imagen->setMascara(mascara);
    imagen->setAncho(ancho);
    imagen->setAlto(alto);
    imagen->setPosicion(x, y);
    imagen->render();
}

void EntidadVista::render() {
    if (!esta_apariencia) return;
    std::unordered_map<std::string, Imagen*> equipables(std::move(parser.getEquipables(apariencia)));
    for (auto& parte: ordenDeImagenes) {
        Imagen * imagen_mostrar = nullptr;
        if (equipables.count(parte)) {
            imagen_mostrar = equipables[parte];
            equipables.erase(parte);
            renderImagen(imagen_mostrar, mascara, getX(), getY(), ancho, alto);
            continue;
        }
        for (auto& imagen: parser.getImagenes(apariencia, parte)) 
            renderImagen(imagen, mascara, getX(), getY(), ancho, alto);
    }
    for (auto& equipable: equipables) 
        renderImagen(equipable.second, mascara, getX(), getY(), ancho, alto);
    animacion_local.avanzar();
    // renderer->setColor(51, 0, 51);
    // renderer->rect(getX(), getY(), getAncho(), getAlto());
}

void EntidadVista::actualizarApariencia(DatosApariencia& apariencia) {
    // TODO: provisorio
    if (apariencia.estado == "101") {
        this->apariencia = {};
        apariencia.tipo = "Fantasma";
    }
    esta_apariencia = true;
    this->apariencia = apariencia;
    ancho = parser.getAnchoReal(apariencia);
    alto = parser.getAltoReal(apariencia);
    animacion_local.setAnimacion(apariencia);
}

bool EntidadVista::contienePunto(int x, int y) {
    SDL_Point punto = { x, y };
    SDL_Rect rect = { getX(), getY(), ancho, alto};
    return SDL_PointInRect(&punto, &rect);
}