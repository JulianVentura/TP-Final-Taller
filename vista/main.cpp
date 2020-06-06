#include "EntornoGrafico.h"
#include "IRenderable.h"
#include "Imagen.h"
#include "Ventana.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <iostream>

class Ejemplo: public IRenderable, public IInteractivo {
public:
    Ejemplo(EntornoGrafico& entorno) {
        entorno.addRenderable(this);
        std::string path("assets/robert.jpg"); 
        imagen = Imagen(entorno, path);

        x = (ventana->getAncho() - imagen.getAncho())/ 2;
        y = (ventana->getAlto() - imagen.getAlto()) / 2;
        r = 100;
        alpha = 0;
        texto = std::string("Holaaa");
    }

    void render() override {
        int xoff = r * cos(alpha);
        int yoff = r * sin(alpha);

        renderer->setColor(100, 51, 100);
        renderer->text(texto);

        renderer->line(x + xoff, y + yoff, 0, 0);
        renderer->line(x + xoff, y + yoff, 0, ventana->getAlto());
        renderer->line(x + xoff, y + yoff, ventana->getAncho(), 0);
        renderer->line(x + xoff, y + yoff, ventana->getAncho(), ventana->getAlto());
        imagen.setPosicion(x + xoff, y + yoff);
        imagen.render();
        alpha += velocidad;
    }

    void manejarEvento(const SDL_Event& event) override {
        if (event.type != SDL_KEYDOWN) return;
        if (event.key.keysym.sym == SDLK_UP) {
            velocidad += 0.01;
        }
        if (event.key.keysym.sym == SDLK_DOWN) {
            velocidad -= 0.01;
        }
    }
private: 
    Imagen imagen;
    int x;
    int y;
    int r;
    float alpha;
    float velocidad = 0.01;
    std::string texto;
};


int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);

        // Ejemplo
        std::string font_path("assets/DejaVuSansMono.ttf"); 
        entorno.loadFont(font_path, 15);
        Ejemplo ejemplo(entorno);

        ventana.addRenderable(&ejemplo);
        ventana.addInteractivo(&ejemplo);
        // --- Ejemplo
        entorno.run();
        
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
