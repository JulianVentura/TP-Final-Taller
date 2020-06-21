#ifndef MAPAVISTA_H
#define MAPAVISTA_H

#include "IRendereable.h"
#include "IInteractivo.h"
#include "Imagen.h"
#include "Tile.h"



class MapaVista: public IRendereable, public IInteractivo, 
                                                        public IDimensionable {
public:
    explicit MapaVista(EntornoGrafico& entorno);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;

private:
    std::vector<Tile> tiles; // Provisorio
    unsigned int columnas;
    unsigned int filas;
    unsigned int ancho_tile;
    unsigned int alto_tile;
};

#endif
