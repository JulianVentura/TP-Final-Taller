#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include <string>

#include "EntornoGrafico.h"
#include "Ventana.h"

class Ejemplo: public IRendereable, // Será un rendereable
               public IInteractivo // Podrá manejar eventos
{
public:
    Ejemplo(EntornoGrafico& entorno): entorno(entorno) {
        entorno.agregarRendereable(this); // Le digo al entorno grafico que me 
                                          // configure la vantana y el renderer
        this->c_x = ventana->getAncho() / 2; // Ahora puedo usar la vantana por ejemplo
        this->c_y = ventana->getAlto() / 2;
        this->color = color_normal;
    }

    void actualizar() override { // Se va a ejecutar automáticamente antes de 
                                 // render (esto si lo agrego a la ventana 
                                 // directamente, o si no, lo llamo yo manualmente
                                 // como en Escena que llama personja.actualiazar)
        int xoff = 50 * cos(alpha);
        int yoff = 50 * sin(alpha);
        this->x = c_x + xoff;
        this->y = c_y + yoff;
        alpha += 0.05;
    }

    void render() override { // Idem actualizar
        renderer->setColor(color);
        renderer->rectSolido(x, y, w, w);
    }

    void manejarEvento(const SDL_Event& event) override { // idem anterior con addInteractivo
        if (event.type == SDL_MOUSEMOTION) {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            SDL_Point mousePoint = {mouseX, mouseY};
            SDL_Rect rect = {x, y, w, w};
            if (SDL_PointInRect(&mousePoint, &rect)) {
                color = color_hover;
            } else {
                color = color_normal;
            }
        }
    }

private:
    EntornoGrafico& entorno; // Entorno gráfico tiene todo lo que necesito para
                             // renderear y además me da la ventana por si 
                             // quiero diseñar en función del tamaño de la ventana.
    int x = 0;
    int y = 0;
    int c_x = 0;
    int c_y = 0;
    int w = 50;
    float alpha = 0;
    SDL_Color color = {};
    SDL_Color color_normal = {51, 0, 51, 255};
    SDL_Color color_hover = {51, 0, 0, 255};
};

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);

        Ejemplo ejemplo(entorno);

        ventana.agregarInteractivo(&ejemplo);
        ventana.agregarRendereable(&ejemplo);

        entorno.correr();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}