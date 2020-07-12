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

MovibleVista::MovibleVista(EntornoGrafico& entorno, IPosicionable* modelo, 
        EntidadParser& parser, DatosApariencia apariencia): 
        modelo(modelo), parser(parser), apariencia(apariencia), 
        animacion(parser, std::string(ANIMACION_BASE)) {
    entorno.agregarRendereable(this);    
    x = modelo->getX();
    y = modelo->getY();
    ultimo_estado = ANIMACION_BASE;
    ancho = parser.getAncho(apariencia.raza);
    alto = parser.getAlto(apariencia.raza);

    if (apariencia.tipo.size() > 0)
        imagenes = parser.getImagenes(apariencia.tipo);
    else
        imagenes = parser.getImagenes(apariencia.raza, apariencia.clase);
}

void MovibleVista::actualizar(unsigned int delta_t) {
    if (!modelo || !modelo->esta_actualizado()) return;
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
    SDL_Point punto = { x, y };
    SDL_Rect rect = { getX(), getY(), ancho, alto};
    return SDL_PointInRect(&punto, &rect);
}
