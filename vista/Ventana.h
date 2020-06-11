#ifndef VENTANA_H
#define VENTANA_H

#include "EntornoGrafico.h"
#include "IInteractivo.h"
#include "IRendereable.h"
#include "IDimensionable.h"
#include "Renderer.h"
#include <SDL2/SDL_events.h>
#include <vector>

class Ventana: public IDimensionable {
public:
    Ventana(EntornoGrafico& entorno, const char* title);
    ~Ventana();
    void manejarEvento(const SDL_Event& event);
    void render();
    int getAncho() override;
    int getAlto() override;
    void agregarRendereable(IRendereable* rendereable);
    void agregarInteractivo(IInteractivo* interactivo);
    
private:
    int ancho = 650;
    int alto = 650;
    SDL_Window* ventana;
    Renderer* renderer;
    SDL_Color color_fondo = {51, 51, 51, 255};
    std::vector<IInteractivo *> interactivos;
    std::vector<IRendereable *> rendereables;
    EntornoGrafico& entorno;
    friend class Renderer;
};
#endif
