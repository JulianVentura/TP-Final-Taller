#include "PersonajeVista.h"
#include <SDL2/SDL_timer.h>
#include <vector>
#include <string>

#define ARRIBA    "Arriba"
#define ABAJO     "Abajo"
#define DERECHA   "Derecha"
#define IZQUIERDA "Izquierda"
#define QUIETO    "-Quieto"

// La idea es que esto se levante de un json.
std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras {
    {
        std::string(ABAJO QUIETO), 
        std::vector<SDL_Rect>{
            {10, 15, 90, 115},
            {130, 15, 90, 115},
            {250, 15, 90, 115}
        }
    },
    {
        std::string(DERECHA QUIETO), 
        std::vector<SDL_Rect>{
            {15, 410, 85, 110},
            {130, 410, 85, 110},
            {255, 410, 85, 110}
        }
    },
    {
        std::string(IZQUIERDA QUIETO), 
        std::vector<SDL_Rect>{
            {20, 150, 85, 110},
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
            {130,  670, 95, 105},
            {245,  665, 95, 100},
            {370,  665, 95, 110},
            {490,  665, 100, 110},
            {605,  670, 115, 110},
            {735,  670, 95, 110},
            {850,  665, 90, 105},
            {975,  665, 95, 105},
            {1090, 665, 100, 110}
        }
    },
    {
        std::string(DERECHA), 
        std::vector<SDL_Rect>{
            {5,    925, 100, 110},
            {135,  925, 95, 110},
            {255,  925, 95, 110},
            {370,  930, 95, 110},
            {480,  930, 115, 110},
            {610,  925, 100, 110},
            {730,  925, 95, 110},
            {860,  925, 95, 100},
            {980,  930, 95, 105},
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

class Animacion {
public:
    Animacion() = default;
    explicit Animacion(Imagen& imagen, const std::string& animacion): 
        imagen(&imagen), animacion_actual(animacion), ultimo_cambio(SDL_GetTicks()) {}
    void actualizar(unsigned int delta_t);
    void setAnimacion(const std::string& animacion);

private:
    Imagen* imagen = NULL;
    std::string animacion_actual;
    unsigned int cuadro = 0;
    unsigned int ultimo_cambio = 0;
    unsigned int ultima_reproduccion = 0;
    unsigned int tiempo_transcurrido = 0;
    unsigned int intervalo_animacion = 1500;
    unsigned int tiempo_por_frame = 150;
};

void Animacion::setAnimacion(const std::string& animacion) {
    if (animacion == animacion_actual) return;
    animacion_actual = animacion;
    cuadro = 0;

    ultima_reproduccion = 0;
    ultimo_cambio = 0;
}

// TODO: Agregar frecuencia entre reproducción y reproducción 
// TODO: Usar el delta_t 
void Animacion::actualizar(unsigned int delta_t) {
    tiempo_transcurrido = SDL_GetTicks();
    // if (tiempo_transcurrido - ultima_reproduccion < intervalo_animacion) return;
    if (tiempo_transcurrido - ultimo_cambio > tiempo_por_frame) {
        SDL_Rect mascara = mascaras[animacion_actual][cuadro];
        imagen->setMascara(mascara.x, mascara.y, mascara.w, mascara.h);
        ultimo_cambio = tiempo_transcurrido;
        ++cuadro;
        if (cuadro == mascaras[animacion_actual].size()) {
            ultima_reproduccion = tiempo_transcurrido;
            cuadro = 0;
        }
    }
}

class Personaje/*Mock*/ {
public:
    void actualizar();
    void moverDerecha();
    void moverIzquierda();
    void moverArriba();
    void moverAbajo();
    void detenerse();

private:
    int x = 0;
    int y = 0;
    int velocidadX = 0; // Esto estaría en el servidor
    int velocidadY = 0; // Esto estaría en el servidor
    friend class PersonajeVista;
};

// Todo esto se consultaría al servidor.
void Personaje::actualizar() {
    x += velocidadX;
    y += velocidadY;
}

void Personaje::moverDerecha() {
    velocidadY = 0;
    velocidadX = 3;
}

void Personaje::moverIzquierda() {
    velocidadY = 0;
    velocidadX = -3;
}

void Personaje::moverArriba() {
    velocidadX = 0;
    velocidadY = -3;
}

void Personaje::moverAbajo() {
    velocidadX = 0;
    velocidadY = 3;
}
void Personaje::detenerse() {
    velocidadX = 0;
    velocidadY = 0;
}

Animacion animacion;
Personaje personajeModelo;

std::string ultimo_estado;
PersonajeVista::PersonajeVista(EntornoGrafico& entorno) {
    entorno.agregarRendereable(this);
    std::string ruta("assets/personaje.png");
    imagen = Imagen(entorno, ruta);
    imagen.setMascara(10, 15, 90, 115);
    ancho = imagen.getAncho();
    alto = imagen.getAlto();

    // Esto después se cambiaría
    personajeModelo.x = (ventana->getAncho() - imagen.getAncho()) / 2;
    personajeModelo.y = (ventana->getAlto() - imagen.getAlto()) / 2;

    personajeModelo.x = 960;
    personajeModelo.y = 300;
    this->x = personajeModelo.x;
    this->y = personajeModelo.y;
    
    animacion = Animacion(imagen, std::string(ABAJO));
    ultimo_estado = ABAJO;
}

static void nuevo_estado(std::string& ultimo_estado, int delta_x, int delta_y) {
    if (delta_x > 0) 
        ultimo_estado = DERECHA;
    else if (delta_x < 0) 
        ultimo_estado = IZQUIERDA;
    else if (delta_y > 0) 
        ultimo_estado = ABAJO;
    else if (delta_y < 0) 
        ultimo_estado = ARRIBA;
}

void PersonajeVista::actualizar() {
    int ultimo_x = this->x;
    int ultimo_y = this->y;
    personajeModelo.actualizar();
    this->x = personajeModelo.x;
    this->y = personajeModelo.y;

    int delta_x = x - ultimo_x;
    int delta_y = y - ultimo_y;
    std::string agregado;
    if (delta_x == 0 && delta_y == 0)
        agregado = QUIETO;

    nuevo_estado(ultimo_estado, delta_x, delta_y);
    animacion.setAnimacion(ultimo_estado + agregado);
    
    imagen.setPosicion(x, y);
    animacion.actualizar(0);
}

void PersonajeVista::render() {
    imagen.render();

    // DEBUG
    renderer->setColor(100, 51, 100);
    renderer->rect(x, y, imagen.getAncho(), imagen.getAlto());
}

// Esto podría ser un Controlador
int ultima_tecla_presionada;
#include <unordered_set>
std::unordered_set<int> teclas_direccionables {
    SDLK_UP,
    SDLK_DOWN,
    SDLK_LEFT,
    SDLK_RIGHT
};

void PersonajeVista::manejarEvento(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        auto& tecla_presionada = event.key.keysym.sym;
        if (tecla_presionada == SDLK_UP) 
            personajeModelo.moverArriba();
        else if (tecla_presionada == SDLK_DOWN) 
            personajeModelo.moverAbajo();
        else if (tecla_presionada == SDLK_LEFT) 
            personajeModelo.moverIzquierda();
        else if (tecla_presionada == SDLK_RIGHT) 
            personajeModelo.moverDerecha();

        if (teclas_direccionables.count(tecla_presionada) > 0)
            ultima_tecla_presionada = tecla_presionada;
    }

    if (event.type == SDL_KEYUP) {
        auto& tecla_soltada = event.key.keysym.sym;
        if (teclas_direccionables.count(tecla_soltada) <= 0) return;
        if (tecla_soltada != ultima_tecla_presionada) return;
        if (tecla_soltada == SDLK_UP) 
            personajeModelo.detenerse();
        else if (tecla_soltada == SDLK_DOWN)
            personajeModelo.detenerse();
        else if (tecla_soltada == SDLK_LEFT)
            personajeModelo.detenerse();
        else if (tecla_soltada == SDLK_RIGHT)
            personajeModelo.detenerse();
        SDL_Log("Keyup");
    }
}
