#ifndef JUEGO_H
#define JUEGO_H
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "DatosPersonaje.h"
#include "LibreriaConjuntoTileParser.h"
#include "CapasParser.h"
#include "MapaParser.h"
#include "EntidadParser.h"
#include "ServidorProxy.h"

#include "../vista/IRendereable.h"
#include "../vista/LibreriaConjuntoTiles.h"
#include "../vista/CapaFrontal.h"
#include "../vista/MapaVista.h"
#include "../vista/Camara.h"
#include "../vista/Escena.h"
#include "../vista/MovibleVista.h"

#include "../controlador/MovibleControlador.h"
#include "../controlador/IInteractivo.h"



class Juego: public IInteractivo, public IRendereable {
public:
    Juego(EntornoGrafico& entorno, std::string& mapa_s, 
                    DatosPersonaje& datos_personaje, ServidorProxy& servidor);
    ~Juego();
    bool manejarEvento(SDL_Event& evento) override;
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void setObjetivoCamara(ITargeteable& objetivo);
    void agregarObstruible(IObstruible* obstruible);
    void agregarNuevo(std::string& id);

private:
    EntornoGrafico& entorno;
    DatosPersonaje& datos_personaje;
    ServidorProxy& servidor;
    nlohmann::json parser;      
    LibreriaConjuntoTileParser libreriaConjuntoTileParser;
    LibreriaConjuntoTiles conjuntoTiles;
    CapasParser capasParser;
    CapaFrontal capaFrontal;
    MapaParser mapaParser;
    MapaVista mapa;
    Camara camara;
    Escena escena;
    MovibleControlador personajeManejable;
    EntidadParser entidadParser;
    std::unordered_map<std::string, std::pair<IPosicionable*, 
                                                    MovibleVista*>> movibles;
    void agregarEntidad(std::string& id, DatosApariencia& apariencia);
};
#endif
