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
        animacion(parser, std::string(ANIMACION_ABAJO)) {
    entorno.agregarRendereable(this);    
    this->x = modelo->getX();
    this->y = modelo->getY();
    ultimo_estado = ANIMACION_ABAJO;
    this->ancho = parser.getAncho();
    this->alto = parser.getAlto();
    if (apariencia.tipo != "")  
        imagenes = parser.getImagenes(apariencia.tipo);
    else
        imagenes = parser.getImagenes(apariencia.raza, apariencia.clase);
}

void MovibleVista::actualizar(unsigned int delta_t) {
    if (!modelo && !modelo->esta_actualizado()) return;
    int ultimo_x = this->x;
    int ultimo_y = this->y;
    this->x = modelo->getX();
    this->y = modelo->getY();
    modelo->consumirActualizacion();
    delta_x = x - ultimo_x;
    delta_y = y - ultimo_y;
    this->delta_t = delta_t;
}

void MovibleVista::render() {
    animacion.actualizarEstado(delta_t, delta_x, delta_y);
    for (auto& tipoImagen: ordenDeImagenes) {
        for (auto& imagen: imagenes[tipoImagen]) {
            animacion.setMascara(imagen);
            imagen->setPosicion(x - ancho / 2, y - alto);
            imagen->render();
        }
    }
    animacion.avanzar();
}

bool MovibleVista::manejarEvento(SDL_Event& evento) {
    SDL_Point mouse = {};
    auto boton = SDL_GetMouseState(&mouse.x, &mouse.y);
    SDL_Rect rect = {x - ancho / 2, y - alto, ancho, alto};
    Camara::transformar(&mouse.x, &mouse.y);

    if (SDL_PointInRect(&mouse, &rect) == SDL_FALSE) return false;
    
    switch(boton) {
		case SDL_BUTTON_LEFT:
        return true;
        break;
		default:
        printf("boton derecho\n");
		break;
	}
    return false;
}

