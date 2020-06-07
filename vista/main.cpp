#include "EntornoGrafico.h"
#include "IRenderable.h"
#include "Imagen.h"
#include "Ventana.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <iostream>

// class Ejemplo: public IRenderable, public IInteractivo {
// public:
//     explicit Ejemplo(EntornoGrafico& entorno) {
//         entorno.addRenderable(this);
//         std::string path("assets/robert.jpg"); 
//         imagen = Imagen(entorno, path);

//         x = (ventana->getAncho() - imagen.getAncho())/ 2;
//         y = (ventana->getAlto() - imagen.getAlto()) / 2;
//         r = 100;
//         alpha = 0;
//         texto = std::string("Holaaa");
//     }

//     void render() override {
//         int xoff = r * cos(alpha);
//         int yoff = r * sin(alpha);

//         renderer->setColor(100, 51, 100);
//         renderer->text(texto);

//         renderer->line(x + xoff, y + yoff, 0, 0);
//         renderer->line(x + xoff, y + yoff, 0, ventana->getAlto());
//         renderer->line(x + xoff, y + yoff, ventana->getAncho(), 0);
//         renderer->line(x + xoff, y + yoff, ventana->getAncho(), 
//                                                             ventana->getAlto());
//         imagen.setPosicion(x + xoff, y + yoff);
//         imagen.render();
//         alpha += velocidad;
//     }

//     void manejarEvento(const SDL_Event& event) override {
//         if (event.type != SDL_KEYDOWN) return;
//         if (event.key.keysym.sym == SDLK_UP) {
//             velocidad += 0.01;
//         }
//         if (event.key.keysym.sym == SDLK_DOWN) {
//             velocidad -= 0.01;
//         }
//     }

// private: 
//     Imagen imagen;
//     int x;
//     int y;
//     int r;
//     float alpha;
//     float velocidad = 0.01;
//     std::string texto;
// };

class Personaje: public IRenderable, public IInteractivo {
public:
    explicit Personaje(EntornoGrafico& entorno) {
        entorno.addRenderable(this);
        std::string path("assets/personaje.png"); 
        imagen = Imagen(entorno, path);
        imagen.setClip(0, 0, 100, 150);

        x = (ventana->getAncho() - imagen.getAncho())/ 2;
        y = (ventana->getAlto() - imagen.getAlto()) / 2;
    }

    void render() override {
        x += velocidadX;
        y += velocidadY;
        renderer->setColor(100, 51, 100);
        imagen.setPosicion(x, y);
        imagen.render();
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
    int x;
    int y;
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
        // x = (ventana->getAncho() - imagen.getAncho())/ 2;
        // y = (ventana->getAlto() - imagen.getAlto()) / 2;
    }

    void render() override {
        imagen.setPosicion(x, y);
        imagen.render();
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
            if (tecla_soltada == SDLK_UP || tecla_soltada == SDLK_DOWN) 
                velocidadY = 0;
            else if (tecla_soltada == SDLK_LEFT || tecla_soltada == SDLK_RIGHT) 
                velocidadX = 0;
        }
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
    Camara(int ancho, int alto): ancho(ancho), alto(alto) {}
    void setTarget(Personaje& personaje); // por ahora
    Vector2D& transformar(Vector2D& punto);
private:
    int ancho;
    int alto;
    Personaje* personaje;
};

class Escena: public IRenderable {
public:
    Escena(EntornoGrafico& entorno): personaje(entorno), mapa(entorno) {
        entorno.addRenderable(this);
        camara = Camara(ventana->getAncho(), ventana->getAlto());
        camara.setTarget(personaje);
    }

    void render() override {
        mapa.render();
        personaje.render();
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

        Mapa mapa(entorno);
        Personaje personaje(entorno);
        ventana.addInteractivo(&mapa);
        ventana.addInteractivo(&personaje);
        ventana.addRenderable(&mapa);
        ventana.addRenderable(&personaje);
        
        // --- Ejemplo  
        entorno.run();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
