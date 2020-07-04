#include "MovibleVista.h"

#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"
#include "Colores.h"

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

MovibleVista::MovibleVista(EntornoGrafico& entorno, Movible& modelo)
        : modelo(modelo) {
    entorno.agregarRendereable(this);
    SDL_Color color = Colores::colorDesdeHexa(modelo.color_fondo);
    imagen = Imagen(entorno, modelo.ruta_imagen, &color);
    this->x = modelo.x;
    this->y = modelo.y;
    animacion = AnimacionEnteDireccionable(imagen, std::move(modelo.mascaras), 
                                                std::string(ANIMACION_ABAJO));
    ultimo_estado = ANIMACION_ABAJO;
    this->ancho = imagen.getAncho();
    this->alto = imagen.getAlto();
}

void MovibleVista::actualizar(unsigned int delta_t) {
    if (!modelo.esta_actualizado) return;
    int ultimo_x = this->x;
    int ultimo_y = this->y;
    this->x = modelo.x;
    this->y = modelo.y;
    modelo.esta_actualizado = false;
    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    animacion.actualizarEstado(delta_t, delta_x, delta_y);
    imagen.setPosicion(x - ancho / 2, y - alto);
}

void MovibleVista::render() {
    imagen.render();
    renderer->setColor(51, 0, 51);
    renderer->rectSolido(x - 5, y - 5   , 10, 10);
    renderer->rect(x - ancho / 2, y - alto, ancho, alto);
    renderer->rect(x - 3, y - 3, 6, 6);
}
