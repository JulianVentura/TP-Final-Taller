#include <iostream>
#include <string>

#include "../modelo/ServidorProxy.h"
#include "../modelo/DatosPersonaje.h"
#include "../modelo/DatosTienda.h"
#include "../modelo/main_login.h"
#include "../modelo/main_juego.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"

int main(int argc, const char* argv[]) {
	DatosPersonaje datos_personaje;
    DatosTienda datos_tienda;
	ServidorProxy servidor(datos_personaje, datos_tienda);

    try {
        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Ventana ventana(entorno, "Argentum Online");
        Renderer renderer(entorno);
        Colores paleta;

        main_login(entorno, ventana, servidor, paleta);
        if (!servidor.estaLogueado()){
        	servidor.terminar();
        	return 0;
        } 
        main_juego(entorno, ventana, servidor, paleta,
         datos_personaje, datos_tienda);
        servidor.terminar();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        servidor.terminar();
    }
    return 0;
}
