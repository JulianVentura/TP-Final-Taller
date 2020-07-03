#include <iostream>
#include <string>

#include "../modelo/BuclePrincipal.h"
#include "../modelo/ServidorProxy.h"
#include "../modelo/DatosPersonaje.h"
#include "../modelo/DatosTienda.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/Escena.h"
#include "../vista/GUI_Principal.h"

#include "CapasParser.h"
#include "../vista/CapaFrontal.h"
#include "../controlador/IInteractivo.h"
#include "../controlador/PersonajeControlador.h"
#include "../vista/ErrorGrafico.h"
#include "../vista/MovibleVista.h"
#include "Personaje.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;
int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Ventana ventana(entorno, "Argentum Online");
        Renderer renderer(entorno);
        Colores paleta;
        DatosPersonaje datos_personaje;
        DatosTienda datos_tienda;

        ServidorProxy servidor("localhost", "3080", datos_personaje,
        datos_tienda);
        GUI_Principal gui(entorno, paleta, datos_personaje, datos_tienda,
         servidor); 
        servidor.salida = &gui.chat_controlador;
        BuclePrincipal bucle(ventana, gui, servidor);
        
        
        // TODO: Provisorio
        // TODO: habría que agregar una cv
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        std::string mapa_s = std::move(servidor.obtenerMapa());
        auto parser = json::parse(mapa_s.c_str());

        LibreriaConjuntoTileParser libreriaConjuntoTileParser(parser);
        LibreriaConjuntoTiles conjuntoTiles(entorno, 
                                                    libreriaConjuntoTileParser);
        CapasParser capasParser(parser, &conjuntoTiles);
        CapaFrontal capaFrontal(capasParser, &conjuntoTiles);


        MapaParser mapaParser(parser);
        MapaVista mapa(entorno, mapaParser, conjuntoTiles);

        std::string personaje_id("human");
        std::string id("personaje1");
        Personaje personajeModelo(personaje_id, servidor);
        PersonajeControlador personajeControlador(personajeModelo);
        MovibleVista personaje(entorno, personajeModelo);
        servidor.agregarPosicionable(id, &personajeModelo);
        capaFrontal.agregarObstruible(&personaje);
        Camara camara(&mapa, &ventana);
        camara.setObjetivo(personaje);
        // TODO: Provisorio ----^

        Escena escena(entorno, camara, mapa, capaFrontal, conjuntoTiles);
        
        bucle.agregarRendereable(&escena);
        bucle.agregarRendereable(&gui);

        bucle.agregarInteractivo(&personajeControlador);

        bucle.correr();
        servidor.terminar();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
