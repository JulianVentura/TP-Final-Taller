#include <SDL2/SDL_events.h>
#include <iostream>
#include <string>

#include "BucleLogin.h"
#include "BuclePrincipal.h"
#include "Juego.h"
#include "ServidorProxy.h"
#include "DatosPersonaje.h"
#include "DatosTienda.h"

#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Principal.h"
#include "../vista/GUI_Login.h"
#include "../vista/ErrorGrafico.h"

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
        GUI_Login gui_login(entorno, paleta, servidor);
        BucleLogin bucle_login(ventana, gui_login, servidor);
        ventana.agregarRendereable(&gui_login);
        bucle_login.correr();
        ventana.borrarRendereables();
       
        // JUEGO EN SI //

        // TODO: <Login provisorio>
        /*
        std::string direccion("localhost");
        std::string servicio("3080");
        std::string id_usuario("jugador");
        std::string password("jugador");
        std::string raza("Humano");
        std::string clase("Paladin");

        datos_personaje.id = id_usuario;
        servidor.conectar(direccion, servicio);
        servidor.enviarNuevaCuenta(id_usuario, password, raza, clase);
        */
        // TODO: </Login provisorio>
        
        BuclePrincipal bucle(ventana);
        std::string mapa_s;
        servidor.obtenerMapaInit(mapa_s);
        Juego juego(entorno, mapa_s, datos_personaje, servidor);
        servidor.comenzar();
        GUI_Principal gui(entorno, paleta, datos_personaje, datos_tienda);
        GUI_PrincipalControlador gui_controllador(servidor, gui);
        
        ventana.agregarRendereable(&juego);
        ventana.agregarRendereable(&gui);
        
        bucle.agregarInteractivo(SDL_MOUSEBUTTONDOWN, &juego);
        bucle.agregarInteractivo(SDL_TEXTINPUT, &gui_controllador);
        bucle.agregarInteractivo(SDL_KEYDOWN, &gui_controllador);
        bucle.agregarInteractivo(SDL_KEYDOWN, &juego);
        bucle.agregarInteractivo(SDL_KEYUP, &juego);
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
