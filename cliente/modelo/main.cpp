#include <iostream>
#include <string>

#include "../modelo/BuclePrincipal.h"
#include "../modelo/ServidorProxy.h"
#include "../vista/Colores.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/Escena.h"
#include "../vista/GUI_Principal.h"
#include "../vista/GUI_BotonInventario.h"
#include "../controlador/GUI_BotonInventario_Controlador.h"

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);

        Ventana ventana(entorno, "Argentum");
        Renderer renderer(entorno);
        Colores paleta;
        GUI_Principal gui(entorno, paleta); 
        ServidorProxy servidor("localhost", "80", gui.chat_controlador);
        BuclePrincipal bucle(ventana, gui, servidor);

        Escena escena(entorno);
        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        ventana.agregarRendereable(&gui);
        
        bucle.correr();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
