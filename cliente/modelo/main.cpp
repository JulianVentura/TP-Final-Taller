#include <iostream>
#include <string>

#include "BucleLogin.h"
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
#include "../vista/GUI_Login.h"
#include "../vista/CapaFrontal.h"
#include "../vista/ErrorGrafico.h"
#include "../vista/MovibleVista.h"

#include "../controlador/IInteractivo.h"
#include "../controlador/MovibleControlador.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;

int main(int argc, const char* argv[]) {
        try{
        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Ventana ventana(entorno, "Argentum Online");
        Renderer renderer(entorno);
        Colores paleta;
        DatosPersonaje datos_personaje;
        DatosTienda datos_tienda;

        ServidorProxy servidor(datos_personaje, datos_tienda);

        // PANTALLA DE LOGIN //
        GUI_Login gui_login(entorno, paleta, servidor);
        BucleLogin bucle_login(ventana, gui_login, servidor);
        bucle_login.agregarRendereable(&gui_login);
        bucle_login.correr();

        // JUEGO EN SI //

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

        std::string humano = "human";
        Movible movibleModelo(humano);
        MovibleControlador movibleControlador(servidor);
        MovibleVista movible(entorno, movibleModelo);
        servidor.agregarPosicionable(datos_personaje.id, &movibleModelo);

        capaFrontal.agregarObstruible(&movible);

        Camara camara(&mapa, &ventana);
        camara.setObjetivo(movible);
        // TODO: Provisorio ----^

        Escena escena(entorno, camara, mapa, capaFrontal, conjuntoTiles);
        
        bucle.agregarRendereable(&escena);
        bucle.agregarRendereable(&gui);
        bucle.agregarInteractivo(&movibleControlador);

        bucle.agregarRendereable(&escena);
        bucle.agregarRendereable(&gui);

        bucle.correr();
        servidor.terminar();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
