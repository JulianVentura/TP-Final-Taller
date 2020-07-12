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

bool MovibleControlador::manejarEvento(SDL_Event& evento) {
    if (evento.type == SDL_KEYDOWN) {
        int tecla_presionada = evento.key.keysym.sym;
        if (!teclas_direccionables.count(tecla_presionada)) return false;
        servidor.enviarMovimiento(teclas_direccionables[tecla_presionada]);
        ultima_tecla_presionada = tecla_presionada;
        return true;
    } else if (evento.type == SDL_KEYUP) {
        auto& tecla_soltada = evento.key.keysym.sym;
        if (tecla_soltada != ultima_tecla_presionada) return false;
        if (!teclas_direccionables.count(tecla_soltada)) return false;
        servidor.enviarMovimiento(MOVIMIENTO::DETENERSE);
        return true;
    }
    return false;
}
