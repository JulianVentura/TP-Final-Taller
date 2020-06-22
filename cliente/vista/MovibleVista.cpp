#include "MovibleVista.h"

#include "PersonajeVista.h"
#include "Animacion.h"
#include "AnimacionEnteDireccionable.h"

#include <SDL2/SDL_timer.h>
#include <vector>
#include <string>
#include <unordered_map>

// Esto quizas debería estar en otra clase.
// La idea es que esto se levante de un json.
std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras {
    {
        std::string(ABAJO QUIETO), 
        std::vector<SDL_Rect>{
            {10,  15, 90, 115},
            {130, 15, 90, 115},
            {250, 15, 90, 115}
        }
    },
    {
        std::string(DERECHA QUIETO), 
        std::vector<SDL_Rect>{
            {15,  410, 85, 110},
            {130, 410, 85, 110},
            {255, 410, 85, 110}
        }
    },
    {
        std::string(IZQUIERDA QUIETO), 
        std::vector<SDL_Rect>{
            {20,  150, 85, 110},
            {140, 150, 85, 110},
            {260, 150, 85, 110}
        }
    },
    {
        std::string(ARRIBA QUIETO), 
        std::vector<SDL_Rect>{
            {15, 285, 90, 105}
        }
    },
    {
        std::string(ABAJO), 
        std::vector<SDL_Rect>{
            {15,   535, 90, 115},
            {135,  530, 90, 110},
            {255,  530, 90, 120},
            {375,  530, 90, 120},
            {495,  530, 90, 120},
            {615,  535, 90, 115},
            {735,  530, 90, 110},
            {855,  530, 90, 120},
            {975,  530, 90, 120},
            {1095, 530, 90, 120}
        }
    },
    {
        std::string(IZQUIERDA), 
        std::vector<SDL_Rect>{
            {5,    670, 115, 110},
            {130,  670, 95,  105},
            {245,  665, 95,  100},
            {370,  665, 95,  110},
            {490,  665, 100, 110},
            {605,  670, 115, 110},
            {735,  670, 95,  110},
            {850,  665, 90,  105},
            {975,  665, 95,  105},
            {1090, 665, 100, 110}
        }
    },
    {
        std::string(DERECHA), 
        std::vector<SDL_Rect>{
            {5,    925, 100, 110},
            {135,  925, 95,  110},
            {255,  925, 95,  110},
            {370,  930, 95,  110},
            {480,  930, 115, 110},
            {610,  925, 100, 110},
            {730,  925, 95,  110},
            {860,  925, 95,  100},
            {980,  930, 95,  105},
            {1080, 930, 115, 110}
        }
    },
    {
        std::string(ARRIBA), 
        std::vector<SDL_Rect>{
            {15,   790, 90, 110},
            {135,  790, 90, 110},
            {255,  790, 90, 120},
            {375,  780, 90, 120},
            {495,  780, 90, 120},
            {615,  790, 90, 110},
            {735,  790, 90, 110},
            {855,  780, 90, 120},
            {975,  785, 90, 120},
            {1095, 780, 90, 120}
        }
    }
};


MovibleVista::MovibleVista(EntornoGrafico& entorno, Personaje& modelo)
        : personajeModelo(modelo) {
    entorno.agregarRendereable(this);
    std::string ruta("assets/personaje.png");
    imagen = Imagen(entorno, ruta);
    // Esto después se cambiaría
    personajeModelo.x = 935;
    personajeModelo.y = 1851;

    this->x = personajeModelo.x;
    this->y = personajeModelo.y;                    // mascaras Habría que ver  
                                                    // cómo pasarlo
                                                    // Y que no sea por copia
    animacion = AnimacionEnteDireccionable(imagen, (mascaras), 
                                                        std::string(ABAJO));
    ultimo_estado = ABAJO;
    ancho = imagen.getAncho();
    alto = imagen.getAlto();
}

void MovibleVista::actualizar(unsigned int delta_t) {
    int ultimo_x = this->x;
    int ultimo_y = this->y;
    personajeModelo.actualizar();
    this->x = personajeModelo.x;
    this->y = personajeModelo.y;
    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    animacion.actualizarEstado(delta_t, delta_x, delta_y);
    imagen.setPosicion(x, y);
}

void MovibleVista::render() {
    imagen.render();
}
