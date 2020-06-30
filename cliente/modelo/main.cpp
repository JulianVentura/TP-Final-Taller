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
#include "../vista/ErrorGrafico.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;
int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Ventana ventana(entorno, "Argentum");
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
        // std::ifstream archivo("assets/mapa.json");
        // if (!archivo.is_open()) 
            // throw ErrorGrafico("No se puedo abrir archivo de mapa\n");
        // json parser;
        // archivo >> parser;
        // std::this_thread::sleep_for(std::chrono::milliseconds( 5000 ));
        // std::string mapa_s = std::move(servidor.obtenerMapa());
        std::string mapa_s = std::move(servidor.obtenerMapa());
        // printf("%s\n", mapa_s.c_str());
        // printf("%c\n", mapa_s.c_str()[0]);   
        // exit(0);
        auto parser = json::parse(mapa_s.c_str());

        LibreriaConjuntoTileParser libreriaConjuntoTileParser(parser);
        LibreriaConjuntoTiles conjuntoTiles(entorno, libreriaConjuntoTileParser);
        CapasParser capasParser(parser, &conjuntoTiles);
        CapaFrontal capaFrontal(capasParser, &conjuntoTiles);


        MapaParser mapaParser(parser);
        MapaVista mapa(entorno, mapaParser, conjuntoTiles);

        std::string personaje_id("human");
        std::string enemigo_id("golum");

        Personaje personajeModelo;

        PersonajeVista personaje(entorno, personajeModelo, personaje_id, servidor);
        Personaje enemigoModelo;
        
        MovibleVista enemigo(entorno, enemigoModelo, enemigo_id);

        capaFrontal.agregarObstruible(&personaje);
        capaFrontal.agregarObstruible(&enemigo);
        Camara camara(&mapa, &ventana);
        camara.setObjetivo(personaje);
        // TODO: Provisorio ----^

        Escena escena(entorno, camara, mapa, capaFrontal, conjuntoTiles);
        
        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        ventana.agregarRendereable(&gui);
        ventana.agregarInteractivo(&personaje);

        bucle.correr();
        servidor.terminar();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
