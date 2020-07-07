#include <SDL2/SDL_events.h>
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

class Juego: /*public IInteractivo,*/ public IRendereable {
public:
    Juego(EntornoGrafico& entorno, std::string& mapa_s);
    // bool manejarEvento(SDL_Event& evento) override;
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void setObjetivoCamara(ITargeteable& objetivo);
    void agregarObstruible(IObstruible* obstruible);

private:
    json parser;
    LibreriaConjuntoTiles conjuntoTiles;
    CapaFrontal capaFrontal;
    MapaVista mapa;
    Camara camara;
    Escena escena;
};

void Juego::agregarObstruible(IObstruible* obstruible) {
    capaFrontal.agregarObstruible(obstruible);
}

void Juego::setObjetivoCamara(ITargeteable& objetivo) {
    camara.setObjetivo(objetivo);
}

void Juego::actualizar(unsigned int delta_t) {
    escena.actualizar(delta_t);
}

void Juego::render() {
    escena.render();
}

Juego::Juego(EntornoGrafico& entorno, std::string& mapa_s):
    parser(json::parse(mapa_s.c_str())),
    conjuntoTiles(entorno, /*std::move*/(LibreriaConjuntoTileParser(parser))),
    capaFrontal(/*std::move*/(CapasParser(parser, conjuntoTiles)), conjuntoTiles),
    mapa(entorno, /*std::move*/(MapaParser(parser)), conjuntoTiles),
    camara(mapa),
    escena(entorno, camara, mapa, capaFrontal, conjuntoTiles) {
        entorno.agregarRendereable(this);
        camara.setMarco(ventana);
    }

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

        // // PANTALLA DE LOGIN //
        // GUI_Login gui_login(entorno, paleta, servidor);
        // BucleLogin bucle_login(ventana, gui_login, servidor);
        // ventana.agregarRendereable(&gui_login);
        // bucle_login.correr();
        // ventana.borrarRendereables();
        // JUEGO EN SI //
        // TODO:            Login provisorio 
        std::string direccion("localhost");
        std::string servicio("3080");
        std::string id_usuario("jugador");
        std::string password("jugador");
        std::string raza("Humano");
        std::string clase("Paladin");
        datos_personaje.id = id_usuario;
        servidor.conectar(direccion, servicio);
        servidor.enviarNuevaCuenta(id_usuario, password, raza, clase);
        
        std::string mapa_s;
        servidor.obtenerMapaInit(mapa_s);

        servidor.comenzar();

        GUI_Principal gui(entorno, paleta, datos_personaje, datos_tienda);
        GUI_PrincipalControlador gui_controllador(servidor, gui);

        BuclePrincipal bucle(ventana);
        Juego juego(entorno, mapa_s);
        // TODO: Provisorio
        // json parser = json::parse(mapa_s.c_str());
        // LibreriaConjuntoTileParser libreriaConjuntoTileParser(parser);
        // LibreriaConjuntoTiles conjuntoTiles(entorno, 
        //                                             libreriaConjuntoTileParser);
        // CapasParser capasParser(parser, &conjuntoTiles);
        // CapaFrontal capaFrontal(capasParser, &conjuntoTiles);

        // MapaParser mapaParser(parser);
        // MapaVista mapa(entorno, mapaParser, conjuntoTiles);

        std::string humano = "human";
        Movible movibleModelo(humano);
        MovibleControlador movibleControlador(servidor);
        MovibleVista movible(entorno, movibleModelo);
        servidor.agregarPosicionable(datos_personaje.id, &movibleModelo);
        juego.agregarObstruible(&movible);

        // Camara camara(&mapa, &ventana);
        juego.setObjetivoCamara(movible);
        // camara.setObjetivo();
        // TODO: Provisorio ----^

        // Escena escena(entorno, camara, mapa, capaFrontal, conjuntoTiles);
        
        ventana.agregarRendereable(&juego);
        ventana.agregarRendereable(&gui);
        
        bucle.agregarInteractivo(SDL_TEXTINPUT, &gui_controllador);
        bucle.agregarInteractivo(SDL_KEYDOWN, &gui_controllador);
        bucle.agregarInteractivo(SDL_KEYDOWN, &movibleControlador);
        bucle.agregarInteractivo(SDL_KEYUP, &movibleControlador);
        bucle.agregarInteractivo(SDL_WINDOWEVENT, &gui_controllador);
        bucle.agregarInteractivo(SDL_MOUSEWHEEL, &gui_controllador);
        bucle.agregarInteractivo(SDL_MOUSEBUTTONDOWN, &gui_controllador);
        
        bucle.correr();
        servidor.terminar();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
