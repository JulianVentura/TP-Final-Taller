#include <iostream>
#include <string>

#include "BuclePrincipal.h"
#include "EntornoGrafico.h"
#include "Ventana.h"
#include "Escena.h"

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);
        BuclePrincipal bucle(ventana);

        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Escena escena(entorno);

        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        
        bucle.correr();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
