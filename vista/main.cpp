#include "EntornoGrafico.h"
#include "IRenderable.h"
#include "Imagen.h"
#include "Ventana.h"
#include "IDimensionable.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <algorithm>
#include <iostream>
#include <string>


class ITargeteable: public IDimensionable {
public:
    virtual int getX();
    virtual int getY();
protected:
    int x;
    int y;
};

int ITargeteable::getX() {
    return x;
}

int ITargeteable::getY() {
    return y;
}


class Personaje: public IRenderable, public IInteractivo, public ITargeteable {
public:
    explicit Personaje(EntornoGrafico& entorno) {
        entorno.addRenderable(this);
        std::string path("assets/personaje.png"); 
        imagen = Imagen(entorno, path);
        imagen.setClip(0, 0, 100, 150);
        ancho = imagen.getAncho();
        alto = imagen.getAlto();
        x = (ventana->getAncho() - imagen.getAncho())/ 2;
        y = (ventana->getAlto() - imagen.getAlto()) / 2;
    }

    void render() override {
        x += velocidadX;
        y += velocidadY;
        renderer->setColor(100, 51, 100);
        imagen.setPosicion(x, y);
        imagen.render();
        // DEBUG
        renderer->rect(x, y, ancho, alto);
    }

    void manejarEvento(const SDL_Event& event) override {
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
private:
    Imagen imagen;
    int velocidadY = 0;
    int velocidadX = 0;
};

class Mapa: public IRenderable, public IInteractivo {
public:
    explicit Mapa(EntornoGrafico& entorno) {
        entorno.addRenderable(this);
        const std::string path("assets/map.jpg");
        imagen = Imagen(entorno, path);
        imagen.setClip(0, 0, ventana->getAncho(), ventana->getAlto());
        imagen.setAncho(ventana->getAncho() * 2);
        imagen.setAlto(ventana->getAlto() * 2);
    }

    void render() override {
        imagen.setPosicion(x, y);
        imagen.render();
        renderer->setColor(0);
        // DEBUG
        renderer->rect(x + 10, y + 10, imagen.getAncho() - 20, 
                                                        imagen.getAlto() - 20);
    }

    void manejarEvento(const SDL_Event& event) override {
        
    }
private:
    Imagen imagen;
    int x = 0;
    int y = 0;
    int velocidadY = 0;
    int velocidadX = 0;
};

struct Vector2D {
    int x;
    int y;
};

class Camara {
public:
    Camara() = default;
    Camara(IDimensionable* contenedor): contenedor(contenedor){}
    void setTarget(ITargeteable& target);
    void centrar(Renderer* renderer);
    void reiniciar(Renderer* renderer);

private:
    IDimensionable* contenedor;
    ITargeteable* target;
    int xoff = 0;
    int yoff = 0;
};

void Camara::setTarget(ITargeteable& target) {
    this->target = &target;
}

static int acotar(int x, int inferior, int superior) {
    if (x < inferior) return inferior;
    if (x > superior) return superior;
    return x;
}

void Camara::centrar(Renderer* renderer) {
    int centro_x = (contenedor->getAncho() - target->getAncho()) / 2;
    int centro_y = (contenedor->getAlto() - target->getAlto()) / 2;
    xoff = acotar(target->getX() - centro_x, 0, contenedor->getAncho());
    yoff = acotar(target->getY() - centro_y, 0, contenedor->getAlto());
    renderer->desplazar(xoff, yoff);
}

void Camara::reiniciar(Renderer* renderer) {
    renderer->desplazar(-xoff, -yoff);
}

class Escena: public IRenderable, public IInteractivo {
public:
    Escena(EntornoGrafico& entorno): personaje(entorno), mapa(entorno) {
        entorno.addRenderable(this);
        camara = Camara(ventana);
        camara.setTarget(personaje);
    }

    void render() override {
        camara.centrar(renderer);
        mapa.render();
        
        renderer->setColor(51, 51, 51);
        personaje.render();
        camara.reiniciar(renderer);
        // DEBUG
        renderer->rectSolido(ventana->getAncho() / 2, ventana->getAlto() / 2, 
                                                                    10, 10);
    }

    void manejarEvento(const SDL_Event& event) override {
        mapa.manejarEvento(event);
        personaje.manejarEvento(event);
    }

private:
    Camara camara;
    Personaje personaje;
    Mapa mapa;
};

int main(int argc, const char* argv[]) {

    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);

        // Ejemplo
        std::string font_path("assets/DejaVuSansMono.ttf"); 
        entorno.loadFont(font_path, 15);
        // Mapa mapa(entorno);
        // Personaje personaje(entorno);
        // ventana.addInteractivo(&mapa);
        // ventana.addInteractivo(&personaje);
        // ventana.addRenderable(&mapa);
        // ventana.addRenderable(&personaje);
        Escena escena(entorno);

        ventana.addInteractivo(&escena);
        ventana.addRenderable(&escena);
        // --- Ejemplo  
        entorno.run();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
