#ifndef VENTANA_H
#define VENTANA_H

#include "EntornoGrafico.h"
#include "IRendereable.h"
#include "IDimensionable.h"
#include "Renderer.h"
#include <SDL2/SDL_events.h>
#include <vector>

class Ventana: public IDimensionable, IRendereable {
public:
    Ventana(EntornoGrafico& entorno, const char* title);
    ~Ventana();

    void manejarEvento(const SDL_Event& event);
    /**
     * @brief Llamará al método render de los rendereables que fueron agregados
     * en el orden que fueron agregados. Luego se presentará en pantalla.
     */
    void render() override;
    void actualizar(unsigned int delta_t) override;

    int getAncho() override;
    int getAlto() override;

    /**
     * @brief A rendereable se le asignan tanto el Renderer como la Ventana.
     * Se agrega a la lista de renderables de la ventana.
     * @post rendereable podrá usar el renderer y la ventana.
     */
    void agregarRendereable(IRendereable* rendereable);
    
private:
    int ancho = 650;
    int alto = 500;
    SDL_Window* ventana;
    Renderer* renderer;
    SDL_Color color_fondo = {51, 51, 51, 255};
    std::vector<IRendereable *> rendereables;
    EntornoGrafico& entorno;
    friend class Renderer;
};
#endif
