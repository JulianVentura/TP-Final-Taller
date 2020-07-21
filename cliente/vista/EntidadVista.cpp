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

EntidadVista::EntidadVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser): 
       modelo(modelo), parser(parser) {
    entorno.agregarRendereable(this);
    x = modelo->getX();
    y = modelo->getY();
    ultimo_estado = ANIMACION_BASE;
    esta_apariencia = false;
}

void EntidadVista::actualizar(unsigned int delta_t) {
    if (!esta_apariencia || !modelo || !modelo->esta_actualizado()) return;
    // if (!esta_apariencia)printf ("no hay apariencia\n");
    // if (!modelo)printf ("no hay modelo\n");
    // if (!modelo->esta_actualizado()) printf ("modelo no actualizado\n");
    
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
    // renderer->setColor(51, 0, 51);
    // renderer->rect(getX(), getY(), getAncho(), getAlto());
}

void EntidadVista::actualizarApariencia(DatosApariencia& apariencia) {
    if (this->apariencia == apariencia) return;
    sprite.actualizar(parser, apariencia);
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