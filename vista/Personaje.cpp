#include "Personaje.h"
#include <SDL2/SDL_timer.h>
#include <vector>
#include <string>

std::vector<SDL_Rect> mascaras{
    {10, 15, 90, 115},
    {130, 15, 90, 115},
    {250, 15, 90, 115}
};
int i = 0;

class Animacion {
public:
    Animacion() = default;
    explicit Animacion(Imagen& imagen): imagen(&imagen), 
                                            ultimo_cambio(SDL_GetTicks()) {}
    void reproducir();
private:
    Imagen* imagen = NULL;
    unsigned int ultimo_cambio = 0;
    unsigned int ultima_reproduccion = 0;
    unsigned int tiempo_transcurrido = 0;
};

void Animacion::reproducir() {
    imagen->render();
    tiempo_transcurrido = SDL_GetTicks();
    if (tiempo_transcurrido - ultima_reproduccion < 1500) return;
    if (tiempo_transcurrido - ultimo_cambio > 150) {
        i++;
        SDL_Rect mascara = mascaras[i % 3];
        imagen->setMascara(mascara.x, mascara.y, mascara.w, mascara.h);
        ultimo_cambio = tiempo_transcurrido;
        if (i == 3) {
            ultima_reproduccion = tiempo_transcurrido;
            i = 0;
        }
    }
}

Animacion animacion;

Personaje::Personaje(EntornoGrafico& entorno) {
    entorno.agregarRendereable(this);
    std::string ruta("assets/personaje.png"); 
    imagen = Imagen(entorno, ruta);
    imagen.setMascara(10, 15, 90, 115);
    ancho = imagen.getAncho();
    alto = imagen.getAlto();
    x = (ventana->getAncho() - imagen.getAncho()) / 2;
    y = (ventana->getAlto() - imagen.getAlto()) / 2;
    animacion = Animacion(imagen);
}

void Personaje::actualizar() {
    x += velocidadX;
    y += velocidadY;
    imagen.setPosicion(x, y);
}

void Personaje::render() {
    animacion.reproducir();

    // imagen.render();
    // DEBUG
    renderer->setColor(100, 51, 100);
    renderer->rect(x, y, ancho, alto);
}

void Personaje::manejarEvento(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        auto& tecla_presionada = event.key.keysym.sym; 
        if (tecla_presionada == SDLK_UP) velocidadY = -2;
        else if (tecla_presionada == SDLK_DOWN) velocidadY = 2;
        else if (tecla_presionada == SDLK_LEFT) velocidadX = -2;
        else if (tecla_presionada == SDLK_RIGHT) velocidadX = 2;
    }
    if (event.type == SDL_KEYUP) {
        auto& tecla_soltada = event.key.keysym.sym; 
        if (tecla_soltada == SDLK_UP) velocidadY = 0;
        else if (tecla_soltada == SDLK_DOWN) velocidadY = 0;
        else if (tecla_soltada == SDLK_LEFT) velocidadX = 0;
        else if (tecla_soltada == SDLK_RIGHT) velocidadX = 0;
    }
}
