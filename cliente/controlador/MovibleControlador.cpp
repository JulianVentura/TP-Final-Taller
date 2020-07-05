#include "MovibleControlador.h"
#include "../../common/CodigosOperacion.h"

#include <SDL2/SDL_keycode.h>
#include <string>
#include <unordered_map>

enum TECLAS_DIRECCIONES {
    TECLA_ARRIBA = SDLK_w,
    TECLA_DERECHA = SDLK_d,
    TECLA_ABAJO = SDLK_s,
    TECLA_IZQUIERDA = SDLK_a
};

MovibleControlador::MovibleControlador(ServidorProxy& servidor): 
    servidor(servidor) {}

std::unordered_map<int, uint32_t> MovibleControlador::teclas_direccionables {
    { TECLA_ARRIBA, MOVIMIENTO::ARRIBA},
    { TECLA_DERECHA, MOVIMIENTO::DERECHA},
    { TECLA_ABAJO, MOVIMIENTO::ABAJO},
    { TECLA_IZQUIERDA, MOVIMIENTO::IZQUIERDA}
};

void MovibleControlador::manejarEvento(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        int tecla_presionada = event.key.keysym.sym;
        if (teclas_direccionables.count(tecla_presionada) > 0)
            servidor.enviarMovimiento(teclas_direccionables[tecla_presionada]);
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
