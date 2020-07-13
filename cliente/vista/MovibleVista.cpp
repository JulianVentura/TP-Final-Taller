#include "MovibleVista.h"

#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"
#include "Colores.h"
#include "Camara.h"

#include <SDL2/SDL_rect.h>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

const std::vector<std::string> MovibleVista::ordenDeImagenes = {
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
    "cabeza"
};

#define NPC_ANIMACION 60

MovibleVista::MovibleVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser): 
        modelo(modelo), parser(parser), animacion(parser, apariencia.tipo) {
    entorno.agregarRendereable(this);    
    x = modelo->getX();
    y = modelo->getY();
    ultimo_estado = ANIMACION_BASE;
    esta_apariencia = false;
}

void MovibleVista::actualizar(unsigned int delta_t) {
    if (!esta_apariencia || !modelo || !modelo->esta_actualizado()) return;
    int ultimo_x = x;
    int ultimo_y = y;
    x = modelo->getX();
    y = modelo->getY();
    modelo->consumirActualizacion();
    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    animacion.actualizarEstado(delta_t, delta_x, delta_y);
    animacion.setMascara(mascara);
    animacion.avanzar();
}

void MovibleVista::render() {
    if (!esta_apariencia) return;
    for (auto& tipoImagen: ordenDeImagenes) {
        for (auto& imagen: imagenes[tipoImagen]) {
            imagen->setMascara(mascara);
            imagen->setAncho(ancho);
            imagen->setAlto(alto);
            imagen->setPosicion(getX(), getY());
            imagen->render();
        }
    }
    renderer->setColor(51, 0, 51);
    renderer->rect(getX(), getY(), getAncho(), getAlto());
}

bool MovibleVista::contienePunto(int x, int y) {
    if (!esta_apariencia) return false;
    SDL_Point punto = { x, y };
    SDL_Rect rect = { getX(), getY(), ancho, alto};
    return SDL_PointInRect(&punto, &rect);
}

void MovibleVista::actualizarApariencia(DatosApariencia& apariencia) {
    if (apariencia.tipo.size() > 0) {
        if (esta_apariencia) return;
        imagenes = parser.getImagenes(apariencia.tipo);
        animacion.setTiempoPorCuadro(NPC_ANIMACION);
    } else {
        imagenes = parser.getImagenes(apariencia.raza, apariencia.clase);
    }
    esta_apariencia = true;
    ancho = parser.getAncho(apariencia.raza, apariencia.tipo);
    alto = parser.getAlto(apariencia.raza, apariencia.tipo);
    animacion.setAnimacion(apariencia.tipo);
}
