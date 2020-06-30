#include "PersonajeVista.h"
#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"
#include "../../common/CodigosOperacion.h"

#include <string>
#include <unordered_set>

// TODO: Esto podría ser un Controlador
int ultima_tecla_presionada;
enum TECLAS_DIRECCIONES {
    TECLA_ARRIBA = SDLK_w,
    TECLA_DERECHA = SDLK_d,
    TECLA_ABAJO = SDLK_s,
    TECLA_IZQUIERDA = SDLK_a
};

const std::unordered_map<int, uint32_t> teclas_direccionables {
    { TECLA_ARRIBA, MOVIMIENTO::ARRIBA},
    { TECLA_DERECHA, MOVIMIENTO::DERECHA},
    { TECLA_ABAJO, MOVIMIENTO::ABAJO},
    { TECLA_IZQUIERDA, MOVIMIENTO::IZQUIERDA}
};

void PersonajeVista::manejarEvento(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        int tecla_presionada = event.key.keysym.sym;
        if (teclas_direccionables.count(tecla_presionada) > 0)
            servidor.enviarMovimiento(teclas_direccionables.at(tecla_presionada));
        if (teclas_direccionables.count(tecla_presionada) > 0)
            ultima_tecla_presionada = tecla_presionada;
    }

    if (event.type == SDL_KEYUP) {
        auto& tecla_soltada = event.key.keysym.sym;
        if (tecla_soltada != ultima_tecla_presionada) return;
        if (teclas_direccionables.count(tecla_soltada) > 0)
            servidor.enviarMovimiento(MOVIMIENTO::DETENERSE);

    }
}

void PersonajeVista::actualizar(unsigned int delta_t) {
    // MovibleVista::actualizar(delta_t);
    int ultimo_x = this->x;
    int ultimo_y = this->y;

    personajeModelo.actualizar();

    auto posiciones = std::move(servidor.obtenerPosiciones());
    if (posiciones.size() <= 0) return;
    personajeModelo.x = posiciones[0].x;
    personajeModelo.y = posiciones[0].y;
    this->x = personajeModelo.x;
    this->y = personajeModelo.y;
    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    animacion.actualizarEstado(delta_t, delta_x, delta_y);
    imagen.setPosicion(x, y);

}
