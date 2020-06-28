#ifndef ESCENA_H
#define ESCENA_H
#include "IRendereable.h"
#include "Camara.h"
#include "MapaVista.h"
#include "Obstaculo.h"

class Escena: public IRendereable{
public:
    explicit Escena(EntornoGrafico& entorno);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event);

private:
    Camara camara;
    MapaVista mapa;
    std::unordered_map<std::string, std::vector<Obstaculo>> capasObstaculos;
    std::vector<std::string> capasOrdenadas;
    std::unordered_map<std::string, std::vector<int>> capasFrente;
    LibreriaConjuntoTiles conjuntosTiles;
    int columnas;
    int filas;
    int ancho_tile;
    int alto_tile;
};
#endif
