#ifndef JUEGO_H
#define JUEGO_H
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

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
#include "../../common/Serializacion.h"


class Juego: public IInteractivo, public IRendereable {
public:
    Juego(EntornoGrafico& entorno, DatosPersonaje& datos_personaje, 
                                                    ServidorProxy& servidor);
    ~Juego();
    bool manejarEvento(SDL_Event& evento) override;
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void setObjetivoCamara(ITargeteable& objetivo);
    void agregarObstruible(IObstruible* obstruible);
    void actualizarPosiciones(std::unordered_map<std::string, std::pair<int, 
                                                            int>> posiciones);
    void actualizarEstados(std::vector<serializacionEstado> estados);

private:
    EntornoGrafico& entorno;
    DatosPersonaje& datos_personaje;
    ServidorProxy& servidor;
    std::string mapa_s;
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
    void agregarEntidad(std::string& id);
    void borrarEntidad(std::string& id);

    std::pair<IPosicionable*, MovibleVista*> crearEntidad(std::string& id, 
                                                DatosApariencia& apariencia);
};
#endif
