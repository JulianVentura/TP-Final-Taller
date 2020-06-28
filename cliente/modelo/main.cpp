#include <iostream>
#include <string>

#include "BuclePrincipal.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/Escena.h"
#include "../vista/GUI_Principal.h"

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);

        Ventana ventana(entorno, "Argentum");
        Renderer renderer(entorno);
        // Colores paleta;
        // GUI_Principal gui(entorno, paleta); 
        // BuclePrincipal bucle(ventana, gui);

        BuclePrincipal bucle(ventana/*, gui*/);

        Escena escena(entorno);
        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        // ventana.agregarRendereable(&gui);
        
        bucle.correr();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
