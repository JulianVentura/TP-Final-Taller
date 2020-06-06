#ifndef VENTANA_H
#define VENTANA_H

#include "EntornoGrafico.h"
#include "IInteractivo.h"
#include "IRenderable.h"
#include "Renderer.h"
#include <SDL2/SDL_events.h>
#include <vector>

class Ventana {
public:
    Ventana(EntornoGrafico& entorno, const char* title);
    ~Ventana();
    void manejarEvento(const SDL_Event& event);
    void render();
    int getAncho();
    int getAlto();
    void addRenderable(IRenderable* renderable);
    void addInteractivo(IInteractivo* interactivo);
private:
    int width = 650;
    int height = 650;
    SDL_Window* ventana;
    Renderer* renderer;
    SDL_Color color_fondo = {51, 51, 51, 255};
    std::vector<IInteractivo *> interactivos;
    std::vector<IRenderable *> renderables;
    EntornoGrafico& entorno;
    friend class Renderer;
};

#endif