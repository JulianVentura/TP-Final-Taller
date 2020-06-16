#include "PersonajeVista.h"
#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"

#include <string>

// Esto podría ser un Controlador
int ultima_tecla_presionada;
enum TECLAS_DIRECCIONES {
    TECLA_ARRIBA = SDLK_w,
    TECLA_DERECHA = SDLK_d,
    TECLA_ABAJO = SDLK_s,
    TECLA_IZQUIERDA = SDLK_a
};

#include <unordered_set>
const std::unordered_set<int> teclas_direccionables {
    TECLA_ARRIBA,
    TECLA_DERECHA,
    TECLA_ABAJO,
    TECLA_IZQUIERDA
};

void PersonajeVista::manejarEvento(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        auto& tecla_presionada = event.key.keysym.sym;
        if (tecla_presionada == TECLA_ARRIBA) 
            personajeModelo.moverArriba();
        else if (tecla_presionada == TECLA_ABAJO) 
            personajeModelo.moverAbajo();
        else if (tecla_presionada == TECLA_IZQUIERDA) 
            personajeModelo.moverIzquierda();
        else if (tecla_presionada == TECLA_DERECHA) 
            personajeModelo.moverDerecha();

        if (teclas_direccionables.count(tecla_presionada) > 0)
            ultima_tecla_presionada = tecla_presionada;
    }

    if (event.type == SDL_KEYUP) {
        auto& tecla_soltada = event.key.keysym.sym;
        if (tecla_soltada != ultima_tecla_presionada) return;
        if (teclas_direccionables.count(tecla_soltada) > 0)
            personajeModelo.detenerse();
    }
}
