#include <iostream>
#include <string>

#include "BuclePrincipal.h"
#include "ServidorProxy.h"
#include "DatosPersonaje.h"
#include "DatosTienda.h"
#include "CapasParser.h"
#include "Movible.h"

#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/Escena.h"
#include "../vista/GUI_Principal.h"
#include "../vista/CapaFrontal.h"
#include "../vista/ErrorGrafico.h"
#include "../vista/MovibleVista.h"

#include "../controlador/IInteractivo.h"
#include "../controlador/MovibleControlador.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;

enum PARAMS {
    EJECUTABLE,
    DIRECCION,
    SERVICIO,
    ID_USUARIO,
    PERSONAJE,
    CANT_PARAMS
};

/**
 * @param argv <direccion> <servicio> <id_usuario> <personaje>
 * @param personaje puede ser human o golum por ahora
 */
int main(int argc, const char* argv[]) {
    try {
        if (argc != CANT_PARAMS) {
            std::cerr << "Parametros incorrectos: uso <direccion> "
                    << "<servicio> <id_usuario> <personaje>"
                    << "\n personaje: human/golum" << std::endl;
            return -1;
        }

        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Ventana ventana(entorno, "Argentum Online");
        Renderer renderer(entorno);
        Colores paleta;
        DatosPersonaje datos_personaje;
        DatosTienda datos_tienda;
        std::string direccion(argv[DIRECCION]);
        std::string servicio(argv[SERVICIO]);
        std::string id_usuario(argv[ID_USUARIO]);

        ServidorProxy servidor(direccion, servicio, id_usuario, datos_personaje,
        datos_tienda);

        GUI_Principal gui(entorno, paleta, datos_personaje, datos_tienda,
         servidor); 
        servidor.salida = &gui.chat_controlador;
        BuclePrincipal bucle(ventana, gui, servidor);
        
        
        // TODO: Provisorio
        // TODO: habría que agregar una cv
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        std::string mapa_s = std::move(servidor.obtenerMapa());
        auto parser = json::parse(mapa_s.c_str());

        LibreriaConjuntoTileParser libreriaConjuntoTileParser(parser);
        LibreriaConjuntoTiles conjuntoTiles(entorno, 
                                                    libreriaConjuntoTileParser);
        CapasParser capasParser(parser, &conjuntoTiles);
        CapaFrontal capaFrontal(capasParser, &conjuntoTiles);

        MapaParser mapaParser(parser);
        MapaVista mapa(entorno, mapaParser, conjuntoTiles);

        std::string id_personaje(argv[PERSONAJE]);

        Movible movibleModelo(id_personaje);
        MovibleControlador movibleControlador(servidor);
        MovibleVista movible(entorno, movibleModelo);
        servidor.agregarPosicionable(id_usuario, &movibleModelo);

        capaFrontal.agregarObstruible(&movible);

        Camara camara(&mapa, &ventana);
        camara.setObjetivo(movible);
        // TODO: Provisorio ----^

        Escena escena(entorno, camara, mapa, capaFrontal, conjuntoTiles);
        
        bucle.agregarRendereable(&escena);
        bucle.agregarRendereable(&gui);
        bucle.agregarInteractivo(&movibleControlador);

        ventana.agregarRendereable(&escena);
        ventana.agregarRendereable(&gui);

        bucle.correr();
        servidor.terminar();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
