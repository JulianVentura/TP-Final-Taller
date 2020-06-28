#ifndef ESCENA_H
#define ESCENA_H
#include "IRendereable.h"
#include "IInteractivo.h"
#include "Camara.h"
#include "MapaVista.h"
#include "PersonajeVista.h"
#include "Obstaculo.h"

class Escena: public IRendereable, public IInteractivo {
public:
    explicit Escena(EntornoGrafico& entorno);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Camara camara;
    Personaje personajeModelo;
    PersonajeVista personaje;
    Personaje enemigoModelo;
    MovibleVista enemigo;
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
