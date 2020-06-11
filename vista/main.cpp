#include <iostream>
#include <string>

#include "EntornoGrafico.h"
#include "Ventana.h"
#include "Escena.h"

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);

        std::string font_path("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(font_path, 15);
        Escena escena(entorno);

        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        entorno.run();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
