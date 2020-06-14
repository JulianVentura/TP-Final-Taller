#include <iostream>
#include <string>

#include "BuclePrincipal.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/Escena.h"
#include "../vista/GUI_Principal.h"

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);
        GUI_Principal gui(entorno); 

        BuclePrincipal bucle(ventana);

        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Escena escena(entorno);

        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        ventana.agregarRendereable(&gui);

        bucle.correr();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
